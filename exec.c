#include "exec.h"
#include "main.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
char **detect_env_variables(char **argv)
{
	char **names = env_get_names();
	int i, j, ni, alen = arr_length(argv), nlen = arr_length(names);

	for (i = 0; i < alen; i++)
		for (j = 0; j < nlen; j++)
		{
			ni = str_contains(argv[i], str_join(2, "$", names[j]));
			if (ni != -1)
				argv[i] = str_replace(argv[i], env_get(names[j]), str_join(2, "$", names[j]));
		}
	
	return (argv);
}*/

/**
 * exec - execute the command.
 * @argv: the array of arguments
 */
void exec(char **argv)
{
	pid_t pid;
	char *filename;
	void (*func)(char **);

	if (!argv || !argv[0])
		return;

	/*argv = detect_env_variables(argv);*/

	filename = argv[0];
	func = exec_get(filename);
	if (func)
	{
		func(argv + 1);
		return;
	}

	if (!file_exists(filename))
	{
		filename = env_search_in_path(filename);
		if (!filename)
			filename = argv[0];
	}

	pid = fork();
	if (pid == 0)
	{
		execve(filename, argv, environ);
		perror(filename);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		perror(env_get("_"));

	wait(NULL);
}

/**
 * exec_exit - command to exit
*/
void exec_exit(char **argv)
{
	int status = 0;

	if (argv[0])
		status = str2int(argv[0]);

	exit(status);
}

/**
 * exec_env - command to print all env variables
*/
void exec_env(char **argv)
{
	char *env;

	if (argv[0])
	{
		env = env_get(argv[0]);
		if (env)
		{
			_puts(env);
			_putchar('\n');
		}
	}
	else
		ll_print(env_all());
}

/**
 * exec_env - command to print all env variables
*/
void exec_env_set(char **argv)
{
	if (!argv[0])
	{
		perror(env_get("_"));
		return;
	}

	env_set(argv[0], argv[1]);
}

/**
 * exec_env - command to print all env variables
*/
void exec_env_unset(char **argv)
{
	if (!argv[0])
	{
		perror(env_get("_"));
		return;
	}

	env_unset(argv[0]);
}

/**
 * exec_get - get executer function
 */
void (*exec_get(char *name))(char **)
{
	exec_t execs[] = {
		{"exit", exec_exit},
		{"env", exec_env},
		{"setenv", exec_env_set},
		{"unsetenv", exec_env_unset},
		{NULL, NULL},
	};

	int i = 0;

	while (execs[i].func != NULL)
	{
		if (strcmp(execs[i].name, name) == 0)
			return (execs[i].func);

		i++;
	}

	return (NULL);
}

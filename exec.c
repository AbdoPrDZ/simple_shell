#include "exec.h"
#include "main.h"

/**
 * detect_env_variables - detect env variables in argv and replace them.
 * @argv: array of argv.
 */
void detect_env_variables(char **argv)
{
	int i;
	char *arg, *start, *end, *var_name, *var_value, *temp;

	for (i = 0; argv[i] != NULL; i++)
	{
		arg = argv[i];
		start = strchr(arg, '$');

		while (start)
		{
			end = start + 1;
			while (*end && (*end == '_' || isalnum(*end)))
			{
				end++;
			}

			if (end > start + 1)
			{
				var_name = malloc(end - start);
				strncpy(var_name, start + 1, end - start - 1);
				var_name[end - start - 1] = '\0';

				var_value = env_get(var_name);
				if (var_value != NULL)
				{
					temp = str_replace(arg, var_value, str_join(2, "$", var_name));
					free(arg);
					arg = temp;
				}

				free(var_name);
			}

			start = strchr(end, '$');
		}

		argv[i] = arg;
	}
}

/**
 * exec - execute the command.
 * @argv: the array of arguments.
 */
void exec(char **argv)
{
	pid_t pid;
	char *filename;
	void (*func)(char **);

	detect_env_variables(argv);

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
 * exec_get - get executer function.
 * @name: name of exec.
 * Return: the pointer of exec function
 */
void (*exec_get(char *name))(char **)
{
	exec_t execs[] = {
		{"exit", exec_exit},
		{"env", exec_env},
		{"setenv", exec_env_set},
		{"unsetenv", exec_env_unset},
		{"cd", exec_chdir},
		{"alias", exec_alias},
		{"unalias", exec_unalias},
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

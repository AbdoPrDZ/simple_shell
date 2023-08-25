#include "alias.h"
#include "exec.h"
#include "shell.h"
#include <errno.h>

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
			while (*end && 
				  (*end == '_' || isalnum(*end) || *end == '$' || *end == '?'))
				end++;

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
 * set_errno - set errno.
 * @status: error status.
 */
void set_errno(int status)
{
	if (WIFEXITED(status))
		errno = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		errno = 128 + WTERMSIG(status);
}

/**
 * exec - execute the command.
 * @shell_filename: the shell filename.
 * @argv: the array of arguments.
 * Return: 1 if success, 0 on error.
 */
int exec(const char *shell_filename, char **argv)
{
	int s, es, (*func)(const char*, char **);
	alias_t *ali;
	pid_t pid;
	char *filename;

	detect_env_variables(argv);
	filename = argv[0];
	func = exec_get(filename);
	if (func)
	{
		s = func(shell_filename, argv + 1), set_errno(s);
		if (s == -1)
			return (0);
		return (1);
	}
	ali = alias_get(filename);
	if (ali)
		argv = get_argv(ali->command), filename = argv[0];
	if (!file_exists(filename))
	{
		filename = env_search_in_path(filename);
		if (!filename)
			filename = argv[0];
	}
	pid = fork();
	if (pid == 0)
	{
		es = execve(filename, argv, environ), set_errno(es);
		if (es == -1)
		{
			perror(shell_filename), exit(EXIT_FAILURE);
			return (0);
		}
		return (1);
	}
	else if (pid == -1)
		perror(env_get("_"));
	else
		wait(&s), set_errno(s);
	return (0);
}

/**
 * exec_get - get executer function.
 * @name: name of exec.
 * Return: the pointer of exec function
 */
int (*exec_get(char *name))(const char*, char **)
{
	exec_t execs[] = {
		{"exit", exec_exit},
		{"env", exec_env},
		{"setenv", exec_env_set},
		{"unsetenv", exec_env_unset},
		{"cd", exec_chdir},
		{"alias", exec_alias},
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

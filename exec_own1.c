#include "shell.h"
#include "arr.h"
#include "alias.h"
#include "exec.h"
#include<unistd.h>
#include <errno.h>

/**
 * exec_exit - command to exit.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_exit(char **argv)
{
	int status = 0;

	if (argv[0])
		status = str2int(argv[0]);
	
	exit(status);
	
	return (status);
}

/**
 * exec_env - command to print all env variables.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_env(char **argv)
{
	char *env;
	linked_list *head;

	if (argv[0])
	{
		env = env_get(argv[0]);
		if (env)
			_puts(str_join(2, env, "\n"));
		else
			return (-1);
	}
	else
	{
		head = env_all();

		while (head->next)
		{
			_puts(str_join(2, head->data, "\n"));
			head = head->next;
		}
	}

	return (0);
}

/**
 * exec_env_set - command to print all env variables.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_env_set(char **argv)
{
	if (!argv[0])
		return (-1);

	env_set(argv[0], argv[1]);

	return (0);
}

/**
 * exec_env_unset - command to print all env variables.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_env_unset(char **argv)
{
	if (!argv[0])
		return (-1);

	env_unset(argv[0]);

	return (9);
}

static char *old_pwd;

/**
 * exec_chdir - move between directories.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_chdir(char **argv)
{
	char *distance = env_get("HOME");
	char *pwd, *cwd;

	if (arr_length((void **)argv) > 1)
	{
		_puts("cd: too many arguments");
		return (-1);
	}

	if (argv[0])
		distance = argv[0];

	if (strcmp(distance, "-") == 0 && old_pwd)
		distance = old_pwd;

	cwd = getcwd(NULL, 0);

	if (chdir(distance) == 0)
	{
		pwd = getcwd(NULL, 0);
		env_set("PWD", pwd);
		old_pwd = str_copy(cwd);
		free(pwd);
		free(cwd);
	}
	else
	{
		_puts(str_join(3, "cd: ", distance, ": No such file or directory\n"));
		return (-1);
	}

	return (0);
}

#include "shell.h"
#include "arr.h"
#include "alias.h"
#include "exec.h"
#include<unistd.h>
#include <errno.h>

/**
 * exec_exit - command to exit.
 * @shell_filename: the shell filename.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_exit(const char *shell_filename, char **argv)
{
	int status = 0, *_status;

	if (argv[0])
	{
		_status = str2int(argv[0]);
		if (_status)
		{
			status = *_status;
			free(_status);
		}
		else
			_puts(str_join(4, shell_filename, ": exit: ", argv[0], ERR2));
	}
	
	exit(status);
	
	return (status);
}

/**
 * exec_env - command to print all env variables.
 * @shell_filename: the shell filename.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_env(const char *shell_filename, char **argv)
{
	linked_list *head;

	if (argv[0])
	{
		_puts(str_join(5, shell_filename, ": env: ‘", argv[0], "‘", ERR1));
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
 * @shell_filename: the shell filename.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_env_set(const char *shell_filename, char **argv)
{
	if (!argv[0])
	{
		_puts(str_join(2, shell_filename, ": setenv: Missing env name\n"));
		return (-1);
	}

	if (arr_length((void **)argv) > 2)
	{
		_puts(str_join(2, shell_filename, ": setenv: too many arguments"));
		return (-1);
	}

	env_set(argv[0], argv[1]);

	return (0);
}

/**
 * exec_env_unset - command to print all env variables.
 * @shell_filename: the shell filename.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_env_unset(const char *shell_filename, char **argv)
{
	int i, len = arr_length((void **)argv);

	if (!argv[0])
	{
		_puts(str_join(2, shell_filename, ": unsetenv: Missing env name\n"));
		return (-1);
	}

	for (i = 0; i < len; i++)
		if (!env_unset(argv[i]))
			_puts(str_join(4, shell_filename, ": unsetenv: ", argv[i], ERR1));

	return (0);
}

static char *old_pwd;

/**
 * exec_chdir - move between directories.
 * @shell_filename: the shell filename.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_chdir(const char *shell_filename, char **argv)
{
	char *distance = env_get("HOME");
	char *pwd, *cwd;

	if (arr_length((void **)argv) > 1)
	{
		_puts(str_join(2, shell_filename, ": cd: too many arguments"));
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

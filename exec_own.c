#include "exec.h"

/**
 * exec_exit - command to exit.
 * @argv: array of argv.
 */
void exec_exit(char **argv)
{
	int status = 0;

	if (argv[0])
		status = str2int(argv[0]);

	exit(status);
}

/**
 * exec_env - command to print all env variables.
 * @argv: array of argv.
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
 * exec_env_set - command to print all env variables.
 * @argv: array of argv.
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
 * exec_env_unset - command to print all env variables.
 * @argv: array of argv.
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

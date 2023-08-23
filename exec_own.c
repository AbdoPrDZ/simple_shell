#include "main.h"
#include "arr.h"
#include "alias.h"
#include "exec.h"
#include<unistd.h>

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

static char *old_pwd;

/**
 * exec_chdir - move between directories.
 * @argv: array of argv.
 */
void exec_chdir(char **argv)
{
	char *distance = env_get("HOME");
	char *pwd, *cwd;

	if (arr_length((void **)argv) > 1)
	{
		_puts("cd: too many arguments");
		return;
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
		_puts(str_join(3, "cd: ", distance, ": No such file or directory\n"));
}

/**
 * exec_alias - create edit delete alias commands.
 * @argv: array of argv.
 */
void exec_alias(char **argv)
{
	int i, alen, ei, vlen;
	char *name, *value;

	alen = arr_length((void **)argv);

	if (alen == 0)
		alias_print_all();
	for (i = 0; i < alen; i++)
	{
		ei = str_contains(argv[i], "=");
		if (ei == -1)
		{
			if(!alias_print(argv[0]))
				_puts(str_join(3, "alias: ", argv[i], ": not found\n"));
		}
		else
		{
			name = malloc(sizeof(char) * (ei));
			strncpy(name, argv[i], ei);
			name[ei] = '\0';
			value = argv[0] + ei + 1;
			vlen = _strlen(value);
			if (value[0] == '"')
				value = value + 1,
				vlen--;
			if (value[vlen - 1] == '"')
				value[vlen - 1] = '\0';
			alias_set(name, value);
		}
	}
}

void exec_unalias(char **argv)
{
	int i, alen = arr_length((void **)argv);

	if (alen == 0)
	{
		_puts("unalias: usage: unalias [-a] name [name ...]\n");
		return;
	}

	if (strcmp(argv[0], "-a") == 0)
		alias_unset_all();
	else
		for (i = 0; i < alen; i++)
			if (!alias_unset(argv[i]))
				_puts(str_join(3, "unalias: ", argv[i], ": not found\n"));
}

#include "shell.h"
#include "arr.h"
#include "alias.h"
#include "exec.h"
#include<unistd.h>
#include <errno.h>

/**
 * exec_alias - create edit delete alias commands.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_alias(char **argv)
{
	int i, alen, ei, vlen, status = 0;
	char *name, *value;

	alen = arr_length((void **)argv);

	if (alen == 0)
		alias_print_all();

	for (i = 0; i < alen; i++)
	{
		ei = str_contains(argv[i], "=");
		if (ei == -1)
		{
			if (!alias_print(argv[0]))
			{
				_puts(str_join(3, "alias: ", argv[i], ": not found\n"));
				status = -1;
			}
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
			status = 0;
		}
	}

	return (status);
}

/**
 * exec_get_pid - get pid
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_get_pid(char **argv)
{
	(void)argv;
	_puts(str_join(2, int2str(getpid()), "\n"));
	return (0);
}

/**
 * exec_last_exit_status - get last exit status.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_last_exit_status(char **argv)
{
	(void)argv;
	_puts(str_join(2, int2str(errno), "\n"));
	return (0);
}

#include "shell.h"
#include "arr.h"
#include "alias.h"
#include "exec.h"
#include<unistd.h>
#include <errno.h>

/**
 * exec_alias - create edit delete alias commands.
 * @shell_filename: the shell filename.
 * @argv: array of argv.
 * Return: exec status.
 */
int exec_alias(char *shell_filename, char **argv)
{
	int i, alen, ei/*, vlen*/, status = 0;
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
				_puts(str_join(4, shell_filename, ": alias: ", argv[i], ": Not found\n"));
				status = -1;
			}
		}
		else
		{
			name = malloc(sizeof(char) * (ei));
			strncpy(name, argv[i], ei);
			name[ei] = '\0';
			value = str_decode(argv[i] + ei + 1);
			alias_set(name, value);
			status = 0;
		}
	}

	return (status);
}

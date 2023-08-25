#include "arr.h"
#include "shell.h"
#include "string.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * handle_signal - checks if Ctrl C is pressed
 * @n: signal number
 */
void handle_signal(int n)
{
	if (n == SIGINT)
		_puts(SHELL_COMMAND_START_MESSAGE);
}

/**
 * handle_eof - end of file handler.
 * @len: the length.
 * @buff: the buffer.
 */
void handle_eof(int len, char *buff)
{
	(void)buff;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buff);
		}
		exit(0);
	}
}

/**
 * _isatty - check if is atty
 */
void _isatty(void)
{
	if (isatty(STDIN_FILENO))
		_puts(SHELL_COMMAND_START_MESSAGE);
}

/**
 * clean_argv - clean arguments from quotes.
 * @argv: array of arguments.
 * Return: cleaned array.
 */
char **clean_argv(char **argv)
{
	int i, len = arr_length((void **)argv), alen;
	char *arg;

	for (i = 0; i < len; i++)
	{
		arg = argv[i];
		alen = _strlen(arg);

		if (alen >= 2 && arg[0] == '"' && arg[alen - 1] == '"')
		{
			argv[i] = str_copy(arg + 1);
			argv[i][alen - 2] = '\0';
			free(arg);
		}
	}

	return (argv);
}
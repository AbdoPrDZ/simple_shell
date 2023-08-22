#include "main.h"
#include "exec.h"
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
 * main - Main function.
 * Return: Always 0.
 */
int main(void)
{
	char *command, **commands;
	size_t csize = 0;
	ssize_t glen;
	int i, clen;

	signal(SIGINT, handle_signal);
	while (1)
	{
		_isatty();
		glen = getline(&command, &csize, stdin);

		handle_eof(glen, command);

		clen = _strlen(command);
		if (clen > 0)
		{
			if (command[clen - 1] == '\n')
				command[clen - 1] = '\0';

			commands = str_arr_clean(str_split(command, ";"));

			for (i = 0; i < arr_length(commands); i++)
			{
				exec(str_arr_clean(str_split(commands[i], " ")));
			}
		}
	}

	free(command);
	arr_free(commands);

	return (0);
}

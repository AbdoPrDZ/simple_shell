#include "main.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * handle_signal - checks if Ctrl C is pressed
 * @num: signal number
 */
void handle_signal(int n)
{
	if (n == SIGINT)
		_puts(SHELL_COMMAND_START_MESSAGE);
}

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

void _isatty(void)
{
	if (isatty(STDIN_FILENO))
		_puts(SHELL_COMMAND_START_MESSAGE);
}

int main(void)
{
	char *input = NULL, **argv;
	size_t isize = 0;
	ssize_t glen;
	int run = 1, ilen;

	signal(SIGINT, handle_signal);
	while (run)
	{
		_isatty();
		glen = getline(&input, &isize, stdin);

		handle_eof(glen, input);

		argv = str_split(input, " \n");

		ilen = strlen(input);
		if (ilen > 0 && input[ilen - 1] == '\n')
			input[ilen - 1] = '\0';

		exec(argv);
	}

	free(input);

	return (0);
}

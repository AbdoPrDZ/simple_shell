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

int main(void)
{
	char *original = "hello world, hello universe!";
    char *replacement = "hi";
    char *target = "hello";

    char *result = str_replace(original, replacement, target);
    if (result) {
        printf("Original: %s\n", original);
        printf("Replacement: %s\n", replacement);
        printf("Target: %s\n", target);
        printf("Result: %s\n", result);
        free(result);
    }

	return (0);
}

/**
 * main - Main function.
 * Return: Always 0.
 */
int mainold(void)
{
	char *command, **commands, **argv;
	size_t isize = 0;
	ssize_t glen;
	int i, ilen;

	signal(SIGINT, handle_signal);
	while (1)
	{
		_isatty();
		glen = getline(&command, &isize, stdin);

		handle_eof(glen, command);

		commands = str_arr_clean(str_split(command, ";"));

		for (i = 0; commands[i]; i++)
		{
			ilen = _strlen(commands[i]);
			if (ilen > 0 && commands[i][ilen - 1] == '\n')
				commands[i][ilen - 1] = '\0';

			argv = str_arr_clean(str_split(commands[i], " "));

			exec(argv);
		}
	}

	free(command);

	return (0);
}

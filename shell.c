#include "shell.h"
#include "arr.h"
#include "exec.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>

/**
 * remove_comment - remove comment from command.
 * @str: this command.
 * Return: modifed command.
 */
char *remove_comment(char *str)
{
	int i = str_contains(str, " #");

	if (i != -1)
		str = str_replace(str, "", str + i);

	return (str);
}

/**
 * remove_comment_all - remove comments from all lines.
 * @text: the text.
 * Return: array of lines.
 */
char **remove_comment_all(char *text)
{
	int i, len;
	char **lines = str_split(text, "\n");

	len = arr_length((void **)lines);

	for (i = 0; i < len; i++)
		lines[i] = remove_comment(lines[i]);

	lines = str_arr_clean(lines);

	return (lines);
}

/**
 * exec_command - execute the command.
 * @shell_filename: the shell filename.
 * @command: the command.
 */
void exec_command(char *shell_filename, char *command)
{
	char **commands = NULL;
	int i, clen = _strlen(command);

	if (command[clen - 1] == '\n')
		command[clen - 1] = '\0';

	commands = str_arr_clean(str_split(command, ";"));

	for (i = 0; i < arr_length((void **)commands); i++)
		exec(shell_filename, str_arr_clean(get_argv(commands[i])));
		
	arr_free((void **)commands);
}

/**
 * exec_file - execute file commands.
 * @shell_filename: the shell filename.
 * @filename: the file name.
 */
void exec_file(char *shell_filename, char *filename)
{
	char *content, **lines;
	int i, len;

	content = file_read(filename);

	if (!content)
		return;
	
	lines = remove_comment_all(content);
	len = arr_length((void **)lines);

	for (i = 0; i < len; i++)
		exec_command(shell_filename, lines[i]);
}

/**
 * main - Main function.
 * @argc: argument count
 * @arg: arguments
 * Return: Always 0.
 */
int main(int argc, char *arg[])
{
	char *input, *command = NULL;
	size_t csize = 0;
	int i, ilen, iq = 0;

	signal(SIGINT, handle_signal);
	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
			if (file_exists(arg[i]))
				exec_file(arg[0], arg[i]);
			else
				_puts(str_join(4, arg[0], ": ", str_join(2, arg[i], ERR1)));
	}
	else
		while (1)
		{
			if (!iq) 
				_isatty();
			else
				_puts("> ");
			handle_eof(getline(&input, &csize, stdin), input);
			input = remove_comment(input), ilen = _strlen(input);
			if (iq && str_contains(input, "\"") == -1)
				command = str_join(2, command, input);
			else if (ilen > 0)
			{
				if (!iq)
				{
					command = str_copy(input);
					if ((str_char_count(input, '\"') % 2) != 0)
						iq = 1;
				}
				else
					command = str_join(2, command, input), iq = 0;
				if (!iq)
					exec_command(arg[0], command);
			}
		};
	free(input), free(command);
	return (0);
}

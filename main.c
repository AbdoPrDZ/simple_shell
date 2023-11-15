#include "shell.h"
#include "arr.h"
#include "exec.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>

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
void exec_command(const char *shell_filename, char *command)
{
	char **commands = NULL, *c_command;
	int i, j = 0, clen = _strlen(command);
	int opai, opoi;

	if (command[clen - 1] == '\n')
		command[clen - 1] = '\0';

	commands = str_arr_clean(str_split(command, ";"));

	for (i = 0; i < arr_length((void **)commands); i++)
	{
		c_command = str_copy(commands[i]);
		clen = _strlen(c_command);
		opai = str_contains(c_command, "&&");
		opoi = str_contains(c_command, "||");
		if (opai != -1 || opoi != -1)
		{
			while (opai != -1 || opoi != -1)
			{
				if ((opai != -1 && opai < opoi) || opoi == -1)
					j = opai;
				else
					j = opoi;
				exec(shell_filename, str_arr_clean(get_argv(str_cut(c_command, 0, j))));
				if (j + 2 < clen)
				{
					c_command = str_copy(c_command + j + 2);
					opai = str_contains(c_command, "&&");
					opoi = str_contains(c_command, "||");
				}
				else
					opai = -1, opoi = -1, free(c_command);
			}
		}
		if (c_command)
			exec(shell_filename, str_arr_clean(get_argv(c_command))), free(c_command);
	}

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
 * start_shell - starting the shell
 * @arg: arguments
 */
void start_shell(char *arg[])
{
	char *input, *command = NULL;
	size_t csize = 0;
	int iq = NOT_IN_QUOTE;

	while (1)
	{
		if (iq == NOT_IN_QUOTE)
			_isatty();
		else
			_puts("> ");
		handle_eof(getline(&input, &csize, stdin), input);
		input = remove_comment(input);
		if (iq == NOT_IN_QUOTE &&
			str_contains(input, "\"") == -1 &&
			str_contains(input, "\'") == -1 &&
			str_contains(input, "`") == -1)
			command = str_copy(input);
		else
		{
			command = str_join(2, command, input);
			if (iq == NOT_IN_QUOTE && (str_char_count(command, '\"') % 2) != 0)
				iq = IN_DOUBLE_QUOTE;
			else if (iq == NOT_IN_QUOTE && (str_char_count(command, '\'') % 2) != 0)
				iq = IN_SINGLE_QUOTE;
			else if (iq == NOT_IN_QUOTE && (str_char_count(command, '`') % 2) != 0)
				iq = IN_BT_QUOTE;

			if ((iq == IN_DOUBLE_QUOTE && (str_char_count(command, '\"') % 2) == 0) ||
				(iq == IN_SINGLE_QUOTE && (str_char_count(command, '\'') % 2) == 0) ||
				(iq == IN_BT_QUOTE && (str_char_count(command, '`') % 2) == 0))
				iq = NOT_IN_QUOTE;
		}

		if (iq == NOT_IN_QUOTE)
			exec_command(arg[0], command), command = "";
	}
	free(command), free(input);
}

/**
 * main - Main function.
 * @argc: argument count
 * @arg: arguments
 * Return: Always 0.
 */
int main(int argc, char *arg[])
{
	int i;

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
		start_shell(arg);

	return (0);
}

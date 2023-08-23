#include "main.h"
#include "string.h"
#include <string.h>

/**
 * _realloc - reallocates memory block.
 * @ptr: previous pointer.
 * @new_size: new size for our pointer.
 * Return: New resized Pointer.
 */
void *_realloc(void *ptr, unsigned int new_size)
{
	unsigned int old_size = sizeof(ptr), i;
	char *new, *old;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new = malloc(new_size);
	old = ptr;

	if (new == NULL)
		return (NULL);

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new[i] = old[i];

		free(ptr);

		for (i = old_size; i < new_size; i++)
			new[i] = '\0';
	}

	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			new[i] = old[i];
		free(ptr);
	}

	return (new);
}

/**
 * file_exists - check if file is exists.
 * @filepath: the file path.
 * Return: 1 if exists, 0 if not.
 */
int file_exists(const char *filepath)
{
	FILE *file = fopen(filepath, "r");
	
	if (file)
	{
		fclose(file);
		return (1);
	}

	return (0);
}

char **get_argv(const char *command)
{
    int num_args = 0, in_quotes = 0, argv_size = 0, arg_length;
    char *arg_start = (char *)command, **argv = NULL, *temp_arg;

    while (*command != '\0')
    {
        if (*command == '"' && (command == arg_start || *(command - 1) != '\\'))
            in_quotes = !in_quotes;

        if (*command == ' ' && !in_quotes)
        {
            arg_length = command - arg_start;
            temp_arg = malloc(sizeof(char) * (arg_length + 1));
            strncpy(temp_arg, arg_start, arg_length);
            temp_arg[arg_length] = '\0';
            if (arg_start != command)
            {
                if (num_args >= argv_size)
                {
                    argv_size += 10;
                    argv = realloc(argv, sizeof(char *) * argv_size);
                }
                argv[num_args++] = str_copy(temp_arg);
            }
            arg_start = (char *)command + 1;
        }

        command++;
    }

    arg_length = command - arg_start;
    temp_arg = malloc(sizeof(char) * (arg_length + 1));
    strncpy(temp_arg, arg_start, arg_length);
    temp_arg[arg_length] = '\0';
    if (arg_start != command)
    {
        if (num_args >= argv_size)
        {
            argv_size += 10;
            argv = realloc(argv, sizeof(char *) * argv_size);
        }
        argv[num_args++] = str_copy(temp_arg);
    }

    if (num_args > 0)
    {
        if (num_args >= argv_size)
        {
            argv_size += 1;
            argv = realloc(argv, sizeof(char *) * argv_size);
        }
        argv[num_args] = NULL;
    }
    else
        free(temp_arg);

    return (argv);
}

#include "shell.h"
#include "string.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

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

/**
 * file_read - get file content.
 * @filename: the filename.
 * Return: file content.
 */
char *file_read(char *filename)
{
	long file_size;
	char *content;
	size_t bytes_read;

	FILE *file = fopen(filename, "r");

	if (!file)
		return (NULL);

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	content = (char *)malloc(file_size + 1);
	if (!content)
	{
		fclose(file);
		return (NULL);
	}

	bytes_read = fread(content, 1, file_size, file);
	if (bytes_read != (size_t)file_size)
	{
		fclose(file);
		free(content);
		fprintf(stderr, "Error reading file\n");
		return (NULL);
	}

	content[file_size] = '\0';

	fclose(file);

	return (content);
}

/**
 * get_argv - get commands arguments
 * @command: the command.
 * Return: array of arguments.
 */
char **get_argv(const char *command)
{
	int i = 0, iq = 0, asize = 0, alen;
	char *astart = (char *)command, **argv = NULL, *tmp;

	while (*command != '\0')
	{
		if (*command == '"' && (command == astart || *(command - 1) != '\\'))
			iq = !iq;

		if (*command == ' ' && !iq)
		{
			alen = command - astart, tmp = malloc(sizeof(char) * (alen + 1));
			strncpy(tmp, astart, alen);
			tmp[alen] = '\0';
			if (astart != command)
			{
				if (i >= asize)
					asize += 10, argv = realloc(argv, sizeof(char *) * asize);
				argv[i++] = str_copy(tmp);
			}
			astart = (char *)command + 1;
		}
		command++;
	}
	alen = command - astart, tmp = malloc(sizeof(char) * (alen + 1));
	strncpy(tmp, astart, alen), tmp[alen] = '\0';
	if (astart != command)
	{
		if (i >= asize)
			asize += 10, argv = realloc(argv, sizeof(char *) * asize);
		argv[i++] = str_copy(tmp);
	}
	if (i > 0)
	{
		if (i >= asize)
			asize += 1, argv = realloc(argv, sizeof(char *) * asize);
		argv[i] = NULL;
	}
	else
		free(tmp);
	return (clean_argv(argv));
}

#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _realloc - reallocates memory block.
 * @ptr: previous pointer.
 * @old_size: old size of previous pointer.
 * @new_size: new size for our pointer.
 * Return: New resized Pointer.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;
	char *old;

	unsigned int i;

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
    else
        return (0);
}

/**
 * arr_length - get array length
 * @arr: the array.
 * Return: the length of array
*/
int arr_length(char **arr)
{
    int i = 0;

    while (arr[i] != NULL)
		i++;

    return (i);
}

/**
 * exec - execute the command.
 * @command: the command.
 * @arc: the arguments length.
 * @argv: the array of arguments
 */
void exec(char **argv)
{
	pid_t pid;
	char *filename;

	if (!argv || !argv[0])
		return;

	filename = argv[0];
	if (!file_exists(filename))
	{
		filename = search_in_path_env(filename);
		if (!filename)
			filename = argv[0];
	}

	pid = fork();
	if (pid == 0)
	{
		execve(filename, argv, environ);
		perror(filename);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		perror(_getenv("_"));

	wait(NULL);
}
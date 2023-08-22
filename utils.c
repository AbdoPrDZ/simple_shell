#include "main.h"
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

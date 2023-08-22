#include "main.h"
#include <string.h>

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
 * arr_remove - remove element from array
 * @arr: the array.
 * @index: index of element.
 * Return: new array.
 */
char **arr_remove(char **arr, int index)
{
	int i, len = arr_length(arr);

	if (!arr || index < 0 || index >= len)
		return (arr);

	free(arr[index]);

	for (i = index; i < len - 1; i++)
		arr[i] = arr[i + 1];

	arr[len - 1] = NULL;

	return (arr);
}

/**
 * arr_free - free up array.
 * @arr: the array wants to free up.
 */
void arr_free(char **arr)
{
	int i;

	if (!arr)
		return;
	
	for (i = 0; arr[i]; i++)
		free(arr[i]);
	
	free(arr);
}

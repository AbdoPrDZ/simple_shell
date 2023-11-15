#include "arr.h"
#include "shell.h"

/**
 * arr_length - get array length
 * @arr: the array.
 * Return: the length of array
 */
int arr_length(void **arr)
{
	int i = 0;

	if (!arr)
		return (0);

	while (arr[i])
		i++;

	return (i);
}

/**
 * arr_remove - remove element from array
 * @arr: the array.
 * @index: index of element.
 * Return: 1 if success, 0 if not.
 */
int arr_remove(void **arr, int index)
{
	int i, len = arr_length(arr);

	if (!arr || index < 0 || index >= len)
		return (0);

	free(arr[index]);

	for (i = index; i < len - 1; i++)
		arr[i] = arr[i + 1];

	arr[len - 1] = NULL;

	return (1);
}

/**
 * arr_free - free up array.
 * @arr: the array wants to free up.
 */
void arr_free(void **arr)
{
	int i;

	if (!arr)
		return;

	for (i = 0; arr[i]; i++)
		free(arr[i]);

	free(arr);
}

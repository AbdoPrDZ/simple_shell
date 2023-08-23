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
 * arr_copy - copy array.
 * @arr: that array want to copy.
 * Return: copied array.
 */
void **arr_copy(void **arr)
{
	int i, len = arr_length(arr);
	void **copy;

	if (!arr)
		return (NULL);

	copy = malloc((len + 1) * sizeof(void *));
	if (!copy)
		return (NULL);

	for (i = 0; i <= len; i++)
		copy[i] = arr[i];

	return (copy);
}

/**
 * arr_add - add item to array.
 * @arr: the array.
 * @item: the item want to add.
 * Return: modifed array.
 */
void **arr_add(void **arr, void *item)
{
	int len;
	void **carr;

	len = arr_length(arr);
	carr = _realloc(arr, sizeof(void *) * (len + 1));
	if (!carr)
		return (NULL);

	carr[len] = item;

	return (carr);
}

/**
 * arr_remove - remove element from array
 * @arr: the array.
 * @index: index of element.
 * Return: new array.
 */
void **arr_remove(void **arr, int index)
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
void arr_free(void **arr)
{
	int i;

	if (!arr)
		return;
	
	for (i = 0; arr[i]; i++)
		free(arr[i]);
	
	free(arr);
}

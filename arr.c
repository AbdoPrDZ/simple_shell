#include "arr.h"
#include "main.h"

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

	while (arr[i] != NULL)
		i++;

	return (i);
}

void **arr_copy(void **arr)
{
    int arr_length = arr_length(arr);
	void **copy;

    if (!arr)
        return (NULL);

    copy = malloc((arr_length + 1) * sizeof(void *));
    if (!copy)
		return (NULL);

    for (int i = 0; i <= arr_length; i++)
        copy[i] = arr[i];

    return copy;
}

void **arr_add(void **arr, void *item)
{
    int len = arr_length(arr);
    void **carr;

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

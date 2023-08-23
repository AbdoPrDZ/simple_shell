#include "main.h"
#include "arr.h"
#include "string.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1, O on Error.
 */
int _putchar(const char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @str: pointer to string
 */
void _puts(const char *str)
{
	int i;

	if (str)
		for (i = 0; i < _strlen(str); i++)
			_putchar(str[i]);
}

/**
 * str2int - converts a string into an integer
 * @s: pointer to a string 
 * Return: the integer
 */
int str2int(char *s)
{
	int i, integer = 0, sign = 1;

	for (i = 0; !((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'); i++)
		if (s[i] == '-')
			sign = sign * (-1);

	for (; (s[i] >= '0') && (s[i] <= '9'); i++)
		integer = (integer * 10) + (sign * (s[i] - '0'));

	return (integer);
}

/**
 * str_arr_clean - clean array from empty strings.
 * @arr: the array.
 * Return: cleaned array.
 */
char **str_arr_clean(char **arr)
{
	int i, j, len;
	char **cleaned_arr;

	if (!arr)
		return (NULL);

	len = arr_length((void **)arr);
	cleaned_arr = malloc(sizeof(char *) * (len + 1));
	if (!cleaned_arr)
		return (NULL);

	for (i = 0, j = 0; i < len; i++)
		if (strcmp(arr[i], "") != 0)
		{
			cleaned_arr[j] = str_copy(arr[i]);
			if (!cleaned_arr[j])
				return (NULL);
			j++;
		}

	cleaned_arr[j] = NULL;

	arr_free((void **)arr);

	return (cleaned_arr);
}

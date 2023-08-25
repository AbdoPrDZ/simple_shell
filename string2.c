#include "shell.h"
#include "string.h"
#include "arr.h"

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
 * @str: pointer to a string 
 * Return: the integer
 */
int *str2int(const char *str)
{
	int i, integer = 0, sign = 1, *result;
	char *cstr = str_clean_spaces_se(str);

	if (!cstr)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] >= '0' && str[i] <= '9') || (i == 0 && str[i] == '-'))
		{
			if (str[i] == '-')
				sign = -1;
			else
				integer = (integer * 10) + (str[i] - '0');
		}
		else
			return (NULL);
	}

	result = malloc(sizeof(int));
	if (result != NULL)
		*result = integer * sign;

	return (result);
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

/**
 * str_char_count - counting char in string.
 * @str: the string.
 * @c: the char.
 * Return: count of c in str.
 */
int str_char_count(const char *str, char c)
{
	int i = 0, j = 0, len = _strlen(str);

	if (!str)
		return (0);

	for (i = 0; i < len; i++)
		if (str[i] == c)
			if (i == 0 || (i > 0 && str[i - 1] != '\\'))
				j++;

	return (j);
}

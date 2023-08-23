#include "string.h"
#include "arr.h"

/**
 * _strlen - it gives the length of a string
 * @s: pointer to the string
 * Return: the length of string
 */
int _strlen(const char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i] != '\0')
		i++;

	return (i);
}

/**
 * str_join - print strings arguments.
 * @n: the length of arguments.
 * Return: joined string.
 */
char *str_join(int n, ...)
{
	int i, j, k, rlen = 0;
	va_list args;
	char *s, *rs;

	va_start(args, n);

	for (i = 0; i < n; i++)
		rlen += _strlen(va_arg(args, char *));

	rs = malloc(sizeof(char) * (rlen + 1));

	if (rs == NULL)
		return (NULL);

	va_end(args);

	va_start(args, n);

	for (i = 0, k = 0; i < n; i++)
	{
		s = va_arg(args, char *);
		if (s)
			for (j = 0; j < _strlen(s); j++, k++)
				rs[k] = s[j];
	}

	rs[k] = '\0';

	va_end(args);

	return (rs);
}

char *str_arr_join(char **arr, char *sep)
{
	int i, alen;
	char *str;

	alen = arr_length((void **)arr);

	if (!arr || alen == 0)
		return (NULL);

	str = arr[0];

	for (i = 1; i < alen; i++)
	{
		str = str_join(2, str, arr[i]);
		if (i < alen - 1)
			str = str_join(2, str, sep);
	}

	return (str);
}

/**
 * str_copy - create allocated copy of string
 * @str: the pointer of string want to copy
 * Return: a pointer of string copy
 */
char *str_copy(const char *str)
{
	int i, len;
	char *new;

	if (!str)
		return (NULL);

	len = _strlen(str);

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);

	for (i = 0; i < len; i++)
		new[i] = str[i];

	new[len] = '\0';

	return (new);
}

/**
 * str_contains - check if target exists in string
 * @str: the string.
 * @target: search target
 * Return: target pos, -1 if not exists.
 */
int str_contains(const char *str, const char *target)
{
	int i, j, s = -1, slen = _strlen(str), tlen = _strlen(target);

	if (tlen > slen)
		return (-1);

	for (i = 0, j = 0; i < slen; i++)
	{
		if (str[i] == target[j])
		{
			if (s == -1)
				s = i;

			j++;

			if (j == tlen)
				return (s);
		}
		else
		{
			s = -1;
			j = 0;
		}
	}

	return (-1);
}

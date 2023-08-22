#include "string.h"

/**
 * _strlen - it gives the length of a string
 * @s: pointer to the string
 * Return: the length of string
 */
int _strlen(const char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
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
		for (j = 0; j < _strlen(s); j++, k++)
			rs[k] = s[j];
	}

	rs[k] = '\0';

	va_end(args);

	return (rs);
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
 * str_split - split a string
 * @str: the string want to split.
 * @imm: the splitter string
 * Return: array of strings
 */
char **str_split(char *str, char *imm)
{
	int i = 0, s = 0, k = 0, item_length, slen = strlen(str), ilen = strlen(imm);
	char **items = malloc(sizeof(char *) * (slen / ilen));

	if (items == NULL)
		return (NULL);

	while (i <= slen)
	{
		if (str[i] == imm[0] || i == slen)
		{
			if (i == slen || strncmp(str + i, imm, ilen) == 0)
			{
				item_length = i - s;

				items[k] = malloc(item_length + 1);

				if (items[k] == NULL)
					return (NULL);

				strncpy(items[k], str + s, item_length);
				items[k][item_length] = '\0';
				s = i + ilen;
				k++;
			}
		}

		i++;
	}

	items[k] = NULL;

	return (items);
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

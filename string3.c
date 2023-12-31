#include "shell.h"
#include "string.h"

/**
 * str_place - replace part of string with new string.
 * @str: the string want to replace.
 * @replace: the replace string.
 * @pos: the position.
 * @keep_old_end: end when replace end or keep old.
 * Return: replaced string.
 */
char *str_place(char *str, char *replace, int pos, int keep_old_end)
{
	int i, j, slen = _strlen(str), rlen = _strlen(replace);
	char *new = str_copy(str);

	if (!str || !replace)
		return (str);
	
	if ((pos + rlen) > slen)
		new = _realloc(new, sizeof(char) * (pos + rlen));

	for (i = pos, j = 0; i < (pos + rlen); i++, j++)
		new[i] = replace[j];

	if (!keep_old_end)
		new[i] = '\0';

	return (new);
}

/**
 * str_replace - replace part of string with new string.
 * @str: the string want to replace.
 * @replace: the replace string.
 * @target: the target string.
 * Return: replaced string.
 */
char *str_replace(const char *str, const char *replace, const char *target)
{
	int tlen, ti;
	char *befor, *after, *new;

	tlen = _strlen(target);
	ti = str_contains(str, target);
	new = str_copy(str);

	if (!str || !new)
		return (NULL);

	if (!replace || ti == -1)
		return (new);

	befor = malloc(sizeof(char) * (ti));
	strncpy(befor, new, ti);
	after = new + ti + tlen;

	new = str_join(3, befor, replace, after);

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
 * str_rev - reverse string.
 * @str: the string.
 * Return: reversed string.
 */
char *str_rev(const char *str)
{
	int i, len = _strlen(str);
	char *reversed = (char *)malloc(len + 1);

	if (reversed == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		reversed[i] = str[len - i - 1];

	reversed[len] = '\0';

	return (reversed);
}

/**
 * int2str - convert int to string.
 * @n: the number.
 * Return: converted string.
 */
char *int2str(int n)
{
	char *str = NULL;
	int sign = 1;
	int i = 0;

	if (n < 0)
		sign = -1, n = -n;

	str = (char *)malloc(11);
	if (!str)
		return (NULL);

	str[i++] = n % 10 + '0';
	n /= 10;
	while (n > 0)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}

	if (sign == -1)
		str[i++] = '-';

	str[i] = '\0';

	str = str_rev(str);

	return (str);
}

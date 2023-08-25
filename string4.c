#include "string.h"

/**
 * str_clean_spaces_se - clean str from spaces in start and end
 * @str: the string want to clean.
 * Return: cleaned string or NULL on error.
 */
char *str_clean_spaces_se(const char *str)
{
	int i = 0, start = 0, end = 0, len;
	char *cstr, *rstr;

	len = _strlen(str);

	while (str[i] && str[i] == ' ')
		start++, i++;

	rstr = str_rev(str);

	i = 0;
	while (rstr[i] && rstr[i] == ' ')
		end++, i++;

	end = len - end;

	cstr = malloc(sizeof(char) * (end - start + 1));
	if (cstr)
	{
		strncpy(cstr, str + start, (end - start));
		cstr[end - start] = '\0';
	}

	return (cstr);
}

/**
 * str_decode - decode string.
 * @str: the string.
 * Return: decoded string.
 */
char *str_decode(const char *str)
{
	int len = strlen(str), i, j = 0, escaped = 0, double_escaped = 0;
	char *decoded = (char *)malloc(len + 1);

	if (decoded == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		if (str[i] == '\\' && !escaped)
			escaped = 1;
		else if (escaped && str[i] == '\\' && !double_escaped)
			double_escaped = 1;
		else
		{
			if (double_escaped)
			{
				decoded[j++] = '\\';
				double_escaped = 0;
			}
			decoded[j++] = str[i];
			escaped = 0;
		}

	decoded[j] = '\0';

	len = _strlen(decoded);

	if (len >= 2 && decoded[0] == '"' && decoded[len - 1] == '"')
	{
		decoded = str_copy(decoded + 1);
		decoded[len - 2] = '\0';
	}

	return (decoded);
}

/**
 * str_cut - cut part of str.
 * @str: string want to cut.
 * @s: string pos.
 * @e: string pos.
 * Return: the part of string.
 */
char *str_cut(const char *str, const int s, const int e)
{
	int i, j, len = _strlen(str);
	char *cstr;

	if (!str || s > e || e > len)
		return (NULL);

	cstr = malloc(sizeof(char) * (e - s + 1));
	if (!cstr)
		return (NULL);

	for (i = s, j = 0; i < e; i++, j++)
		cstr[j] = str[i];

	cstr[j] = '\0';

	return (cstr);
}

/**
 * str_str_count - counting str in str
 * @str: the string.
 * @target: ths target string.
 * Return: count of str in str.
 */
int str_str_count(const char *str, const char *target)
{
	int c = 0, s = 0, ti, len = _strlen(str), tlen = _strlen(target);

	if (!str || !target || tlen > len)
		return (0);

	ti = str_contains(str, target);

	while (ti != -1)
	{
		c++;
		s = ti + tlen;
		ti = str_contains(str + s, target);
	}

	return (c);
}

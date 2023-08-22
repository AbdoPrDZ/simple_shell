#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

/**
 * _strlen - it gives the length of a string
 * @s: pointer to the string
 * Return: the length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
		i++;

	return (i);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @str: pointer to string
 */
void _puts(char *str)
{
	int i;

	if (str)
		for (i = 0; i < _strlen(str); i++)
			_putchar(str[i]);
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
char *str_copy(char *str)
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
	int i = 0, s = 0, k = 0, slen = strlen(str), ilen = strlen(imm);
	char **items = malloc(sizeof(char *) * (slen / ilen));

	if (items == NULL)
		return (NULL);

	while (i <= slen)
	{
		if (str[i] == imm[0] || i == slen)
		{
			if (i == slen || strncmp(str + i, imm, ilen) == 0)
			{
				int item_length = i - s;
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
 * str_place - replace part of string with new string
 * @str: the string want to replace.
 * @replace: the replace string.
 * @pos: the position.
 * @keep_old_end: end when replace end or keep old
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

char *str_replace(const char *str, const char *replace, const char *target)
{
    int ti = str_contains(str, target);
    
    if (!str || !replace || ti == -1) {
        return str_copy(str);
    }

    int slen = _strlen(str);
    int rlen = _strlen(replace);
    int tlen = _strlen(target);
    int newLen = slen + (rlen - tlen) * ((slen / tlen) + 1);

    char *new = (char *)malloc(newLen + 1);
    if (!new) {
        return NULL;
    }

    const char *srcPos = str;
    char *destPos = new;

    while (ti != -1) {
        strncpy(destPos, srcPos, ti);
        destPos += ti;
        srcPos += ti + tlen;

        strcpy(destPos, replace);
        destPos += rlen;

        ti = str_contains(srcPos, target);
    }

    strcpy(destPos, srcPos);
    return new;
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

	for (;(s[i] >= '0') && (s[i] <= '9'); i++)
		integer = (integer * 10) + (sign * (s[i] - '0'));

	return (integer);
}

/**
 * str_arr_clean - clean array from empty strings.
 * @arr: the array.
 * Remove: cleaned array.
 */
char **str_arr_clean(char **arr)
{
    int i, j, len;
    char **cleaned_arr;

    if (!arr)
        return (NULL);

    len = arr_length(arr);
    cleaned_arr = malloc(sizeof(char *) * (len + 1));
    if (!cleaned_arr)
	{
        perror(env_get("_"));
		return (NULL);
    }

    for (i = 0, j = 0; arr[i]; i++)
        if (strcmp(arr[i], "") != 0)
		{
            cleaned_arr[j] = str_copy(arr[i]);
            if (!cleaned_arr[j])
			{
        		perror(env_get("_"));
				return (NULL);
            }
            j++;
        }

    cleaned_arr[j] = NULL;

    for (i = 0; arr[i]; i++)
        free(arr[i]);

    free(arr);

    return (cleaned_arr);
}

int str_contains(char *str, char *target)
{
	int i, j, s = 0, slen = _strlen(str), tlen = _strlen(target);

	if (tlen > slen)
		return (-1);

	for (i = 0, j = 0; i < slen; i++)
	{
		if (!s && str[i] == target[0])
			s = i;
		else if (s && str[i] != target[j])
			return (-1);
		else if (s)
			j++;
	}
	
	return (s);
}

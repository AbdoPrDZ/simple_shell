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

	for (i = 0; i < _strlen(str); i++)
		_putchar(str[i]);
}

/**
 * str_join - print strings arguments.
 * @separator: the separator string.
 * @n: the length of arguments.
 */
char *str_join(int n, ...)
{
    int i, j, k, rsLen = 0;
    va_list args;
    char *s, *rs;

    va_start(args, n);

    for (i = 0; i < n; i++)
        rsLen += _strlen(va_arg(args, char *));

    rs = malloc(sizeof(char) * (rsLen + 1));

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
	int i, j;
	char **array;
	char *token;
	char *copy;

	copy = str_copy(str);

	token = strtok(copy, imm);
	array = malloc((sizeof(char *) * 2));
	array[0] = str_copy(token);

	for (i = 1, j = 3; token; i++, j++)
	{
		token = strtok(NULL, imm);
		array = _realloc(array, (sizeof(char *) * (j - 1)), (sizeof(char *) * j));
		array[i] = str_copy(token);
	}

	free(copy);

	return (array);
}

/**
 * str2int - converts a string into an integer
 *@s: pointer to a string 
 *Return: the integer
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

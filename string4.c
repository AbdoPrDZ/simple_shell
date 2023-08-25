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

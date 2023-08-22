#include "main.h"
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

#include "shell.h"
#include "alias.h"
#include "arr.h"
#include "string.h"
#include <string.h>

static alias_t **alias;

/**
 * alias_index_of - get alias index by name.
 * @name: the name of alias.
 * Return: index of alias.
 */
int alias_index_of(const char *name)
{
	int i, alen = arr_length((void **)alias);

	if (alen == 0 || !name)
		return (-1);
	
	for (i = 0; i < alen; i++)
		if (strcmp(alias[i]->name, name) == 0)
			return (i);
	
	return (-1);
}

/**
 * alias_get - get alias by name.
 * @name: the name of alias.
 * Return: the alias.
 */
alias_t *alias_get(char *name)
{
	int i = alias_index_of(name);

	if (i != -1)
		return (alias[i]);
	
	return (NULL);
}

/**
 * alias_set - create or edit alias command.
 * @name: the name of alias.
 * @command: the alias command.
 */
void alias_set(const char *name, const char *command)
{
	int alen, ii;
	alias_t *item = malloc(sizeof(alias_t));

	alen = arr_length((void **)alias);
	ii = alias_index_of(name);

	item->name = str_copy(name);
	item->command = str_copy(command);

	if (ii != -1)
		alias[ii] = item;
	else
	{
		alias = _realloc(alias, sizeof(alias_t) * (alen + 1));
		alias[alen] = item;
	}
}

/**
 * alias_print - print alias element.
 * @name: the name of alias.
 * Return: 1 if success, 0 if not.
 */
int alias_print(char *name)
{
	alias_t *item = alias_get(name);

	if (item)
		_puts(str_join(5, "alias ", item->name, "=", item->command, "\n"));
	else
		return (0);

	return (1);
}

/**
 * alias_print_all - print all alias elements
 */
void alias_print_all(void)
{
	int i, alen = arr_length((void **)alias);

	for (i = 0; i < alen; i++)
	{
		_puts("alias ");
		_puts(alias[i]->name);
		_puts("='");
		_puts(alias[i]->command);
		_puts("'\n");
	}
}

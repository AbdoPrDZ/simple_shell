#include "main.h"
#include "alias.h"
#include "arr.h"
#include "string.h"
#include <string.h>

static alias_t **alias;

int alias_index_of(const char *name)
{
    int i, alen = arr_length((void**)alias);

    if (alen == 0)
        return (-1);
    
    for (i = 0; i < alen; i++)
        if(strcmp(alias[i]->name, name) == 0)
            return (i);
    
    return (-1);
}

void alias_set(const char *name, const char *command)
{
    int alen, ii;
    alias_t *item = malloc(sizeof(alias_t));

    alen = arr_length((void**)alias);
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

int alias_unset(const char *name)
{
    int ii = alias_index_of(name);

    if (ii == -1)
        return (0);

    alias = (alias_t **)arr_remove((void**)alias, ii);

    return (1);
}

void alias_unset_all(void)
{
    int i, alen = arr_length((void **)alias);

    for (i = 0; i < alen; i++)
        alias_unset(alias[i]->name);
}

int alias_print(char *name)
{
    int i = alias_index_of(name);

    if (i != -1)
        _puts(str_join(4, alias[i]->name, "=", alias[i]->command, "\n"));
    else
        return (0);

    return (1);
}

void alias_print_all(void)
{
    int i, alen = arr_length((void**)alias);

    for (i = 0; i < alen; i++)
        _puts(str_join(4, alias[i]->name, "=", alias[i]->command, "\n"));
}

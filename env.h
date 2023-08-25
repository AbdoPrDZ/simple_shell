#ifndef ENV_H
#define ENV_H

#include "linked_list.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

linked_list *env_all(void);
int env_get_index(const char *name);
char *env_get(char *name);
void env_set(char *name, char *value);
int env_unset(char *name);
char *env_search_in_path(char *filename);

#endif /* ENV_H */

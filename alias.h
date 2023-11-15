#ifndef ALIAS_H
#define ALIAS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct alias_t - pointer of alias commands.
 * @name: alias name.
 * @command: alias command.
 */
typedef struct alias_t
{
	char *name;
	char *command;
} alias_t;

void alias_set(const char *name, const char *command);
alias_t *alias_get(char *name);
void alias_unset_all(void);
int alias_print(char *name);
void alias_print_all(void);

#endif /* ALIAS_H */

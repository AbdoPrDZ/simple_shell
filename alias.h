#ifndef ALIAS_H
#define ALIAS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct alias_t
{
	char *name;
	char *command;
} alias_t;

void alias_set(const char *name, const char *command);
int alias_unset(const char *name);
void alias_unset_all();
int alias_print(char *name);
void alias_print_all(void);

#endif /* ALIAS_H */
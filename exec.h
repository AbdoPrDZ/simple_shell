#ifndef EXEC_H
#define EXEC_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct exec_t - pointer to executer function
 * @name: executer name
 * @func: executer function
 */
typedef struct exec_t
{
	char *name;
	void (*func)(char **);
} exec_t;

void exec(char **argv);
void (*exec_get(char *name))(char **);

#endif /* EXEC_H */
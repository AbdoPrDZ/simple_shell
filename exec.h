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
	void (*exec)(void);
} exec_t;

void exec(char **argv);
void exec_exit(void);
void (*exec_get(char *name))(void);

#endif /* EXEC_H */
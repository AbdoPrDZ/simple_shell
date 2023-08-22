#ifndef EXEC_H
#define EXEC_H

#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

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

/* own */
void exec_exit(char **argv);
void exec_env(char **argv);
void exec_env_set(char **argv);
void exec_env_unset(char **argv);

#endif /* EXEC_H */

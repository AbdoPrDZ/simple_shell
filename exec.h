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
	int (*func)(char*, char **);
} exec_t;

void exec(char *shell_filename, char **argv);
int (*exec_get(char *name))(char *, char **);

/* own */
int exec_exit(char *shell_filename, char **argv);
int exec_env(char *shell_filename, char **argv);
int exec_env_set(char *shell_filename, char **argv);
int exec_env_unset(char *shell_filename, char **argv);
int exec_chdir(char *shell_filename, char **argv);
int exec_alias(char *shell_filename, char **argv);

#endif /* EXEC_H */

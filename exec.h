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
	int (*func)(const char*, char **);
} exec_t;

int exec(const char *shell_filename, char **argv);
int (*exec_get(char *name))(const char *, char **);

/* own */
int exec_exit(const char *shell_filename, char **argv);
int exec_env(const char *shell_filename, char **argv);
int exec_env_set(const char *shell_filename, char **argv);
int exec_env_unset(const char *shell_filename, char **argv);
int exec_chdir(const char *shell_filename, char **argv);
int exec_alias(const char *shell_filename, char **argv);

#endif /* EXEC_H */

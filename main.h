#ifndef MAIN_H
#define MAIN_H

#define SHELL_COMMAND_START_MESSAGE "(abdali-shell)$ "

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/* utils */
void *_realloc(void *ptr, unsigned int new_size);
int file_exists(const char *filepath);
char **get_argv(const char *command);

#endif /* MAIN_H */

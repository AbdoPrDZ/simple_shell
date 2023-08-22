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

/* arr */
int arr_length(char **arr);
char **arr_remove(char **arr, int index);
int arr_contains(char **arr, char *item);
void arr_free(char **arr);

#endif /* MAIN_H */

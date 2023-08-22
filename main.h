#ifndef MAIN_H
#define MAIN_H

#define SHELL_COMMAND_START_MESSAGE "(abdali-shell)$ "

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/* Utils*/
void *_realloc(void *ptr, unsigned int new_size);
int file_exists(const char *filepath);
int arr_length(char **arr);
char **arr_remove(char **arr, int index);
int arr_contains(char **arr, char *item);

/* String */
int _strlen(char *s);
int _putchar(char c);
void _puts(char *str);
char *str_join(int n, ...);
char *str_copy(char *str);
char **str_split(char *str, char *imm);
char *str_place(char *str, char *replace, int pos, int keep_old_end);
char *str_replace(char *str, char *replace, char *target);
int str2int(char *s);
char **str_arr_clean(char **arr);
int str_contains(char *str, char *target);

/* Env */
linked_list *env_all(void);
char *env_get(char *name);
void env_set(char *name, char *value);
void env_unset(char *name);
char **env_get_names(void);
char *env_search_in_path(char *filename);

#endif /* MAIN_H */

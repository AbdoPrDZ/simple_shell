#ifndef MAIN_H
#define MAIN_H

#define SHELL_COMMAND_START_MESSAGE "(abdali-shell)$ "

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/* Utils*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void exec(char **argv);
int file_exists(const char *filepath);
int arr_length(char **arr);

/* String */
int _strlen(char *s);
int _putchar(char c);
void _puts(char *str);
char *str_join(int n, ...);
char *str_copy(char *str);
char **str_split(char *str, char *spl);
int str2int(char *s);

/* Env */
char *_getenv(const char *name);
void _setenv(char **argv);
void _unsetenv(char **argv);
char *search_in_path_env(char *filename);

#endif /* MAIN_H */

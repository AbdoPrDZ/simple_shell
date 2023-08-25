#ifndef MAIN_H
#define MAIN_H

#define SHELL_COMMAND_START_MESSAGE "(abdali-shell)$ "
#define ERR1 ": No such file or directory\n"
#define ERR2 ": numeric argument required\n"

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/* utils */
void *_realloc(void *ptr, unsigned int new_size);
int file_exists(const char *filepath);
char *file_read(char *filename);
char **get_argv(const char *command);
char **clean_argv(char **argv);
void handle_signal(int n);
void handle_eof(int len, char *buff);
void _isatty(void);

#endif /* MAIN_H */

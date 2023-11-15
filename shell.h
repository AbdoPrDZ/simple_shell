#ifndef MAIN_H
#define MAIN_H

#define SHELL_COMMAND_START_MESSAGE "(abdopr-shell)$ "
#define ERR1 ": No such file or directory\n"
#define ERR2 ": numeric argument required\n"

#define NOT_IN_QUOTE 0
#define IN_SINGLE_QUOTE 1
#define IN_DOUBLE_QUOTE 2
#define IN_BT_QUOTE 3

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

char **remove_comment_all(char *text);
void exec_command(const char *shell_filename, char *command);
void exec_file(char *shell_filename, char *filename);
void start_shell(char *arg[]);

/* utils */
void *_realloc(void *ptr, unsigned int new_size);
int file_exists(const char *filepath);
char *file_read(char *filename);
char **get_argv(const char *command);
char **clean_argv(char **argv);
void handle_signal(int n);
void handle_eof(int len, char *buff);
void _isatty(void);
char **clean_argv(char **argv);
char *remove_comment(char *str);

#endif /* MAIN_H */

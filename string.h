#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

int _strlen(const char *s);
int _putchar(const char c);
void _puts(const char *str);
char *str_join(int n, ...);
char *str_copy(const char *str);
char **str_split(char *str, char *imm);
char *str_place(char *str, char *replace, int pos, int keep_old_end);
char *str_replace(const char *str, const char *replace, const char *target);
int *str2int(const char *str);
char **str_arr_clean(char **arr);
int str_contains(const char *str, const char *target);
int str_char_count(const char *str, char c);
char *str_rev(const char *str);
char *int2str(int n);
char *str_clean_spaces_se(const char *str);
char *str_decode(const char *str);
char *str_cut(const char *str, const int s, const int e);

#endif /* STRING_H */

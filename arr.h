#ifndef ARR_H
#define ARR_H

#include <stdio.h>
#include <stdlib.h>

int arr_length(void **arr);
void **arr_remove(void **arr, int index);
void arr_free(void **arr);
void **arr_copy(void **arr);
void **arr_add(void **arr, void *item);

#endif /* ARR_H */
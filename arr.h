#ifndef ARR_H
#define ARR_H

#include <stdio.h>
#include <stdlib.h>

int arr_length(void **arr);
int arr_remove(void **arr, int index);
void arr_free(void **arr);

#endif /* ARR_H */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct linked_list - Linked list of strings
 * @data: sting
 * @next: pointer to next node
 */
typedef struct linked_list
{
	void *data;
	struct linked_list *next;
} linked_list;

linked_list *ll_add_end(linked_list *head, void *data);
linked_list *ll_from_string(char *str, char *imm);
void ll_free(linked_list *head);

#endif /* LINKED_LIST_H */

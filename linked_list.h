#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct linked_list - Linked list of strings
 * @str: sting
 * @next: pointer to next node
 */
typedef struct linked_list
{
	char *str;
	struct linked_list *next;
} linked_list;

linked_list *ll_add_end(linked_list **head, char *str);
linked_list *ll_from_string(char *str, char *imm);
void ll_free(linked_list *head);
void ll_print(linked_list *head);

#endif /* LINKED_LIST_H */

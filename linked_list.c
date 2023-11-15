#include "shell.h"
#include "arr.h"
#include "linked_list.h"
#include "string.h"

/**
 * ll_add_end - add node in the end of linked list.
 * @head: the pointer of head.
 * @data: the item data.
 * Return: the new pointer oh head.
 */
linked_list *ll_add_end(linked_list *head, void *data)
{
	linked_list *tmp, *node;

	node = malloc(sizeof(linked_list));

	if (!node || !data)
		return (NULL);

	node->data = data;
	node->next = NULL;

	if (head)
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;

		tmp->next = node;
	}
	else
		head = node;

	return (head);
}

/**
 * ll_from_string - create linked list from string by split the string
 * @str: the string.
 * @imm: the splitter string.
 * Return: head of linked list
 */
linked_list *ll_from_string(char *str, char *imm)
{
	linked_list *head = NULL;
	char **strs;
	int i, slen;

	strs = str_split(str_copy(str), imm);

	slen = arr_length((void **)strs);

	for (i = 0; i < slen; i++)
		head = ll_add_end(head, (void *)strs[i]);

	return (head);
}

/**
 * ll_free - free the linked list
 * @head: the pointer of head
 */
void ll_free(linked_list *head)
{
	linked_list *tmp;

	while (head)
	{
		tmp = head->next;
		free(head->data);
		free(head);
		head = tmp;
	}
}

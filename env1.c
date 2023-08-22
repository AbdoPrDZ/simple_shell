#include "main.h"
#include "env.h"

/**
 * env_all - get all env variables as linked list
 * Return: linked list of env variables
 */
linked_list *env_all(void)
{
	linked_list *head;
	int i;

	head = malloc(sizeof(linked_list));
	head->str = environ[0];

	for (i = 1; environ[i]; i++)
	{
		head = ll_add_end(&head, environ[i]);
	}

	return (head);
}

/**
 * env_length - get env variables length
 * Return: length of variables
 */
int env_length(void)
{
	int i = 0;

	while (environ[i])
		i++;

	return (i);
}

/**
 * env_get_index - get index of env by name
 * @name: name of env variable
 * Return: index of env variable
 */
int env_get_index(const char *name)
{
	int i, j = 0;

	if (!name)
		return (-1);

	for (i = 0; environ[i]; i++, j = 0)
		if (name[j] == environ[i][j])
		{
			for (; name[j]; j++)
				if (name[j] != environ[i][j])
					break;

			if (name[j] == '\0')
				return (i);
		}

	return (-1);
}

/**
 * env_get - gets the value of env variable
 * @name: name of env variable
 * Return: string of value
 */
char *env_get(char *name)
{
	int i;

	if (!name)
		return (NULL);

	i = env_get_index(name);
	if (i != -1)
		return (environ[i] + _strlen(name) + 1);

	return (NULL);
}

/**
 * env_set - edit or create env variable
 * @name: name of variable
 * @value: variable value.
 */
void env_set(char *name, char *value)
{
	int i, elen = env_length();

	i = env_get_index(name);
	if (i != -1)
		environ[i] = str_place(environ[i], value, _strlen(name) + 1, 0);
	else
	{
		environ[elen] = str_join(3, name, "=", value);
		environ[elen + 1] = '\0';
	}
}

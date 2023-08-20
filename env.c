#include "main.h"
#include "linked_list.h"

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
 * _getenv - gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_getenv(const char *name)
{
	int i, j = 0;
	char *value;

	if (!name)
		return (NULL);

	for (i = 0; environ[i]; i++, j = 0)
		if (name[j] == environ[i][j])
		{
			for (; name[j]; j++)
				if (name[j] != environ[i][j])
					break;

			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}

	return (0);
}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 * @argv: array of entered words
 */
void _setenv(char **argv)
{
	int i, j, k;

	if (!argv[1] || !argv[2])
	{
		perror(_getenv("_"));
		return;
	}

	for (i = 0, j = 0; environ[i]; i++)
		if (argv[1][j] == environ[i][j])
		{
			for (; argv[1][j]; j++)
				if (argv[1][j] != environ[i][j])
					break;

			if (argv[1][j] == '\0')
			{
				
				for (k = 0; argv[2][k]; k++)
					environ[i][j + 1 + k] = argv[2][k];

				environ[i][j + 1 + k] = '\0';

				return;
			}
		}

	if (!environ[i])
	{
		environ[i] = str_join(3, argv[1], "=", argv[2]);
		environ[i + 1] = '\0';
	}
}

/**
 * _unsetenv - Remove an environment variable
 * @argv: array of entered words
 */
void _unsetenv(char **argv)
{
	int i, j;

	if (!argv[1])
	{
		perror(_getenv("_"));
		return;
	}
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (argv[1][j] == environ[i][j])
		{
			while (argv[1][j])
			{
				if (argv[1][j] != environ[i][j])
					break;

				j++;
			}
			if (argv[1][j] == '\0')
			{
				free(environ[i]);
				environ[i] = environ[i + 1];
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				return;
			}
		}
	}
}

/**
 * search_in_path_env - search if filename exists in path_env dirs
 * @filename: the filename want to search.
 * Return: full path if exists, Null of not
*/
char *search_in_path_env(char *filename)
{
	char *full_path;

	linked_list *tmp;

	tmp = ll_from_string(_getenv("PATH"), ":");

	while (tmp)
	{
		full_path = str_join(3, tmp->str, "/", filename);
	
		if (file_exists(full_path))
			return (full_path);

		free(full_path);
		tmp = tmp->next;
	}

	return (NULL);
}

#include "env.h"
#include "arr.h"
#include "shell.h"

/**
 * env_unset - remove env variable
 * @name: env variable name.
 * Return: 1 if success, or 0 if not.
 */
int env_unset(char *name)
{
	return (arr_remove((void **)environ, env_get_index(name)));
}

/**
 * env_search_in_path - search if filename exists in path_env dirs
 * @filename: the filename want to search.
 * Return: full path if exists, Null of not
 */
char *env_search_in_path(char *filename)
{
	char *full_path;

	linked_list *tmp;

	tmp = ll_from_string(env_get("PATH"), ":");

	while (tmp)
	{
		full_path = str_join(3, tmp->data, "/", filename);
	
		if (file_exists(full_path))
			return (full_path);

		free(full_path);
		tmp = tmp->next;
	}

	return (NULL);
}

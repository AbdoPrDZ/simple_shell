#include "exec.h"
#include "main.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * exec - execute the command.
 * @argv: the array of arguments
 */
void exec(char **argv)
{
	pid_t pid;
	char *filename;
  void (*exec)(void);

	if (!argv || !argv[0])
		return;

	filename = argv[0];
  exec = exec_get(filename);
  if (exec)
  {
    exec();
    return;
  }

	if (!file_exists(filename))
	{
		filename = search_in_path_env(filename);
		if (!filename)
			filename = argv[0];
	}

	pid = fork();
	if (pid == 0)
	{
		execve(filename, argv, environ);
		perror(filename);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
		perror(_getenv("_"));

	wait(NULL);
}

/**
 * exec_exit - command to exit
*/
void exec_exit(void)
{
  exit(0);
}

/**
 * exec_env - command to print all env variables
*/
void exec_env(void)
{
  ll_print(env_all());
}

/**
 * exec_get - get executer function
*/
void (*exec_get(char *name))(void)
{
  exec_t execs[] = {
    {"exit", exec_exit},
    {NULL, NULL},
  };

  int i = 0;

  while (execs[i].exec != NULL)
	{
		if (strcmp(execs[i].name, name) == 0)
			return (execs[i].exec);

		i++;
	}

  return (NULL);
}

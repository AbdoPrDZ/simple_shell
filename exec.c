#include "main.h"
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

	if (!argv || !argv[0])
		return;

	filename = argv[0];
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

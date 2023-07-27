#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * execute_command - Execute a command in the shell.
 * @command: The command to execute.
 *
 * Return: 0 on success, or 1 on failure.
 */

int execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		char *executable = find_executable(command);

		if (executable == NULL)
		{
			fprintf(stderr, "%s: command not found\n", command);
			exit(EXIT_FAILURE);
		}
		else
		{
			char *args[] = {executable, NULL};

			execve(executable, args, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	return (pid);
}

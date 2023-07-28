#include "shell.h"

/**
 * execute_command - Execute the given command.
 * @args: Null-terminated array of arguments (command and its arguments).
 *
 * Return: 0 on success, 1 on failure or if the command does not exist.
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (is_builtin(args[0]))
	{
		if (execute_builtin(args) == -1)
			return (1);
	}
	else
	{
		pid = fork();

		if (pid < 0)
		{
			perror(args[0]);
			return (1);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror(args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	return (0);
}

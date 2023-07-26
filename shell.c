#include "shell.h"
#include <sys/wait.h>
#include <unistd.h>

/**
 * display_prompt - Displays the shell prompt.
 */

void display_prompt(void)
{
	printf("($) ");
}

/**
 * execute_command - Executes the given command with arguments.
 * @args: The array of pointers to arguments (command and its arguments).
 *
 * Return: 1 on success, -1 on error.
 */

int execute_command(char **args)
{
	pid_t pid, wpid;
	int status;

	/* Fork a new process*/
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		/* Child process*/

		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
	/* Parent process*/

	do {
		wpid = waitpid(pid, &status, WUNTRACED);
		if (wpid == -1)
		{
			perror("waitpid");
			return (-1);
		}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));

	}

	return (1);
}

/**
 * execute_command_line - Executes a single command line.
 * @input: The input command line.
 */

void execute_command_line(char *input)
{
	char **args;
	int status;

	args = split_input(input);
	if (args[0] != NULL)
	{
		if (strcmp(args[0], "exit") == 0)
		{
			free_args(args);
			free(input);
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			print_environment();
			free_args(args);
			free(input);
			return;
		}

		status = execute_command(args);
		if (status == -1)
			fprintf(stderr, "%s: %s: not found\n", args[0], args[0]);
	}

	free_args(args);
	free(input);
}

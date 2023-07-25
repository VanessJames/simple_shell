#include "shell.h"

/**
 * execute_builtin - Execute a built-in shell command.
 * @command: The command to be executed.
 * @args: An array of arguments for the command.
 *
 * Description: This function checks if the given command
 * is a built-in shell command
 * (e.g., "exit" or "env"). If the command is a built-in, it calls the
 * corresponding built-in function (handle_exit or handle_env) to handle
 * the command execution. It passes any required arguments to the
 * corresponding built-in function.
 *
 * Return: 1 if the command is a built-in and has been executed successfully,
 * 0 otherwise.
 */

static int execute_builtin(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		return (1);
	}
	else if (strcmp(command, "env") == 0)
	{
		handle_env();
		return (1);
	}
	return (0);
}

/**
 * execute_external - Execute an external shell command.
 * @command: The command to be executed.
 * @args: An array of arguments for the command.
 *
 * Description: This function forks a child process to
 * execute an external shell
 * command (a non-built-in command). It uses the execve system call
 * to replace the child process image with the specified command.
 * If the fork or execve operation encounters an error, it displays
 * an error message using perror. The parent process waits for the
 * child process to complete using the wait system call.
 *
 * Return: 1 if the command is an external command and has been
 * executed successfully,0 otherwise.
 */

static int execute_external(char *command, char *args[])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
	{
	if (execve(command, args, environ) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS); /* This line should not be reached*/
	}
	else
	{
		int status;

		if (wait(&status) == -1)
		{
			perror("wait");
			return (0);
		}
		return (1);
	}
}

/**
 * execute_command - Execute a shell command.
 * @command: The command to be executed.
 * @args: An array of arguments for the command.
 *
 * Description: This function checks if the given command is
 * a built-in shell command
 * or an external shell command. If the command is a built-in, it calls
 * the execute_builtin function to handle the command execution.
 * If the command is an external command, it calls the
 * execute_external function to handle the command execution.
 *
 * Return: 1 if the command has been executed successfully
 * (built-in or external), 0 otherwise.
 */

int execute_command(char *command, char *args[])
{
	if (execute_builtin(command))
		return (1);
	if (execute_external(command, args))
		return (1);
	return (execute_external(command, args));
}

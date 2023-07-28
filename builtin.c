#include "shell.h"

/**
 * is_builtin - Check if the given command is a built-in.
 * @command: The command to check.
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int is_builtin(char *command)
{
	char *builtins[] = {
		"exit",
		"env",
		NULL
	};

	int i = 0;

	while (builtins[i] != NULL)
	{
		if (_strcmp(command, builtins[i]) == 0)
		return (1);
		i++;
	}

	return (0);
}

/**
 * execute_builtin - Execute the given built-in command.
 * @args: Null-terminated array of arguments (command and its arguments).
 *
 * Return: 0 on success, -1 on failure.
 */
int execute_builtin(char **args)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		exit(EXIT_SUCCESS);
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		print_environment();
		return (0);
	}

	return (-1);
}

/**
 * print_environment - Print the current environment.
 */
void print_environment(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

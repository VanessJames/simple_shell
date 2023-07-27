#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * execute_builtin - Execute a built-in shell command.
 * @args: An array of strings containing arguments for the built-in command.
 *
 * Return: 0 on success, or 1 on failure or if the command is not a built-in.
 */

int execute_builtin(char **args)
{
	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
			return (0);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
	if (args[1] == NULL)
	{
		char *home_dir = getenv("HOME");

		if (home_dir == NULL)
		{
			fprintf(stderr, "cd: No home directory.\n");
			return (1);
		}
		if (chdir(home_dir) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		char *previous_dir = getenv("PROMPT_DIR");

		if (previous_dir == NULL)
		{
			fprintf(stderr, "cd: No previous directory.\n");
			return (1);
		}
		if (chdir(previous_dir) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		char *previous_dir = getenv("PWD");

		if (previous_dir == NULL)
		{
			fprintf(stderr, "cd: Unable to get current directory.\n");
			return (1);
		}
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (1);
		}
		set_variable("PWD", args[1]);
		set_variable("PROMPT_DIR", previous_dir);
	}
	return (0);
}


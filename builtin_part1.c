#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * is_builtin - Check if a command is a built-in shell command.
 * @command: The command to check.
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */

int is_builtin(char *command)
{
	const char *builtins[] = {"exit", "env", "cd", "alias", NULL};

	for (int i = 0; builtins[i] != NULL; i++)
	{
		if (strcmp(command, builtins[i]) == 0)
		{
			return (1);
		}
	}

    return (0);
}

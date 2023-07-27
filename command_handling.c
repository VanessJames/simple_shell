#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * split_command_line - Split the command line into individual arguments.
 * @command_line: The command line to be split.
 *
 * Return: An array of strings containing the individual arguments.
 */
char **split_command_line(char *command_line)
{
	int buffer_size = 64;
	char **args = (char **) malloc(buffer_size * sizeof(char *));

	if (!args)
	{
		perror("malloc");
		return (NULL);
	}

	char *token;
	int index = 0;
	const char *delimiters = " \t\r\n\a";

	token = strtok(command_line, delimiters);
	while (token != NULL)
	{
		args[index++] = token;

		if (index >= buffer_size)
		{
			buffer_size += 64;
			args = (char **)realloc(args, buffer_size * sizeof(char *));
			if (!args)
			{
				perror("realloc");
				return (NULL);
			}
		}

		token = strtok(NULL, delimiters);

	}
	args[index] = NULL;
	return (args);
}

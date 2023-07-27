#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * remove_comments - Remove comments from the command line.
 * @command_line: The command line with comments to be removed.
 *
 * Return: A new string with comments removed or NULL on failure.
 */
char *remove_comments(char *command_line)
{
	char *new_command = NULL;
	int new_size = 0;
	int i, j;
	int len = strlen(command_line);
	int in_quote = 0;

	new_command = (char *)malloc(len + 1);
	if (!new_command)
	{
		perror("malloc");
		return (NULL);
	}

	for (i = 0, j = 0; i < len; i++)
	{
		if (command_line[i] == '"' || command_line[i] == '\'')
		{
			in_quote = !in_quote;
		}

		if (command_line[i] == '#' && !in_quote)
		{
			while (i < len && command_line[i] != '\n')
			{
				i++;
			}
		}
		else
		{
			new_command[new_size++] = command_line[i];
		}
	}

	new_command[new_size] = '\0';
	return (new_command);
}

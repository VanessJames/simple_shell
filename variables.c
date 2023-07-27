#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 * replace_variables - Replace special variables in the command line.
 * @command_line: The command line containing variables to be replaced.
 *
 * Return: A new string with variables replaced or NULL on failure.
 */
char *replace_variables(char *command_line)
{
	char *new_command = NULL;
	int new_size = 0;
	int len = strlen(command_line);

	new_command = (char *)malloc(len + 1);
	if (!new_command)
	{
		perror("malloc");
		return (NULL);
	}
	for (int i = 0; i < len; i++)
	{
		if (command_line[i] == '$')
		{
			char variable[3] = {0};
			int k = 0;

			i++;
			while (command_line[i] && k < 2 && command_line[i] != ' ')
			{
				variable[k++] = command_line[i++];
			}
			if (strcmp(variable, "?") == 0)
			{
				new_size += append_exit_status(new_command, &new_size);
			}
			else if (strcmp(variable, "$") == 0)
			{
				new_size += append_pid(new_command, &new_size);
			}
			else
			{
				new_size += append_variable(new_command, &new_size, variable);
			}
			i--;
		}
		else
		{
			new_command[new_size++] = command_line[i];
		}
	}
	new_command[new_size] = '\0';
	return (new_command);
}

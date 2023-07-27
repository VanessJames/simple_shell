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
	int i, j;
	int len = strlen(command_line);

	new_command = (char *)malloc(len + 1);

	if (!new_command)
	{
		perror("malloc");
		return (NULL);
	}
	for (i = 0, j = 0; i < len; i++)
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
			char exit_status[4];

			sprintf(exit_status, "%d", get_exit_status());
			int exit_status_len = strlen(exit_status);

			for (k = 0; k < exit_status_len; k++)
			{
				new_command[new_size++] = exit_status[k];
			}
		}
		else if (strcmp(variable, "$") == 0)
		{
			char pid[10];

			sprintf(pid, "%d", getpid());
			int pid_len = strlen(pid);

			for (k = 0; k < pid_len; k++)
			{
				new_command[new_size++] = pid[k];
			}
		}
		else
		{
			for (k = 0; k < 2; k++)
			{
				if (variable[k] != 0)
				{
					new_command[new_size++] = variable[k];
				}
			}
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

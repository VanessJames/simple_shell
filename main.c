#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 * main_loop - The main loop of the simple shell program.
 *
 * Return: Always 0.
 */
int main_loop(void)
{
	char *line = NULL;
	size_t line_buf_size = 0;
	ssize_t characters_read;
	char **args;
	int status;

	while (1)
	{
		display_prompt();
		characters_read = getline(&line, &line_buf_size, stdin);

		if (characters_read == -1)
		{
			if (line != NULL)
			{
				free(line);
			}
			printf("\n");
			break;
		}
		args = parse_command_line(line);
		if (args == NULL || args[0] == NULL)
		{
			continue;
		}
		if (is_builtin(args[0]))
		{
			status = execute_builtin(args);
		}
		else
		{
			status = execute_command(args[0]);
		}
		free_args(args);
		if (status != 0)
		{
			fprintf(stderr, "Error: command execution failed\n");
		}
	}
	return (0);
}
/**
 * main - Entry point of the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	return (main_loop());
}

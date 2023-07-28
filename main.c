#include "shell.h"

/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		line = display_prompt();
		if (!line)
		break;

	args = parse_line(line);
	if (!args)
	{
		free(line);
		continue;
	}

	status = execute_command(args);

	free(line);
	free_args(args);

	} while (status != SHELL_EXIT);

	return (0);
}

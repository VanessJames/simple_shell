#include "shell.h"

/**
 * main - Entry point for the shell program.
 *
 * Return: Always 0 on successful completion.
 */

int main(void)
{
	char *input;
	size_t len = 0;

	do {
		display_prompt();
		input = NULL;
		getline(&input, &len, stdin);

		if (input != NULL)
		{
			execute_command_line(input);
			free(input);
		}
	} while (1);

	return (EXIT_SUCCESS);
}

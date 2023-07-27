#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * shell_read_line - Read a line of input from the user.
 *
 * Return: A pointer to the dynamically allocated
 * input line or NULL on failure.
 */
char *shell_read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;

	characters_read = getline(&line, &bufsize, stdin);
	if (characters_read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

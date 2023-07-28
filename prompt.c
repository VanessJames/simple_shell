#include "shell.h"

/**
 * display_prompt - Display the prompt for the user.
 *
 * Return: A pointer to the user input (command line).
 */
char *display_prompt(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;

	write(STDOUT_FILENO, "$ ", 2);

	chars_read = getline(&line, &bufsize, stdin);

	if (chars_read == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		return (NULL);
	}

	if (line[chars_read - 1] == '\n')
		line[chars_read - 1] = '\0';

	return (line);
}

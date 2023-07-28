#include "shell.h"

/**
 * parse_line - Parse the user input into an array of arguments.
 * @line: The user input (command line) to be parsed.
 *
 * Return: A null-terminated array of arguments (command and its arguments).
 */
char **parse_line(char *line)
{
	char **args;
	char *token;
	int bufsize = TOKEN_BUFSIZE;
	int position = 0;

	args = (char **)malloc(bufsize * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		args[position] = token;
		position++;

	if (position >= bufsize)
	{
		bufsize += TOKEN_BUFSIZE;
		args = (char **)realloc(args, bufsize * sizeof(char *));
		char **token = malloc(sizeof(char *) * (token_bufsize + 1));

		if (!args)
		{
			perror("realloc");
			return (NULL);
		}
	}
		token[position] = NULL;
		token = strtok(NULL, " \t\r\n\a");
	}
	args[position] = NULL;

	return (args);
}

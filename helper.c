#include "shell.h"
#include <unistd.h>

/**
 * split_input - Tokenizes the input command into individual arguments.
 * @input: The input command to be tokenized.
 *
 * Return: An array of pointers to the individual arguments.
 */
char **split_input(char *input)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *arg;
	char *rest = input;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while ((arg = get_next_arg(&rest)) != NULL)
	{
		tokens[position] = arg;
		position++;

	if (position >= bufsize)
	{
		bufsize += 64;
		tokens = realloc(tokens, bufsize * sizeof(char *));
		if (!tokens)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
	}
}

	tokens[position] = NULL;
	return (tokens);
}

/**
 * get_next_arg - Helper function to get the next
 * argument from the input string.
 * @input: The input string containing the command and arguments.
 *
 * Return: A pointer to the next argument,
 * or NULL if no more arguments are present.
 */

char *get_next_arg(char **input)
{
	char *arg = *input;
	char *end;

	if (*arg == '\0')
		return (NULL);

	while (*arg == ' ' || *arg == '\t' || *arg == '\n' ||
		*arg == '\r' || *arg == '\a')
	arg++;

	if (*arg == '\0')
		return (NULL);

	end = arg;

	while (*end != ' ' && *end != '\t' && *end != '\n'
		&& *end != '\r' && *end != '\a' && *end != '\0')
	end++;

	if (*end == '\0')
		*input = end;
	else
	{
		*end = '\0';
		*input = end + 1;
	}

	return (arg);
}

/**
 * free_args - Frees the memory allocated for the arguments.
 * @args: The array of pointers to arguments to be freed.
 */

void free_args(char **args)
{
	int i = 0;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * print_environment - Prints the current environment variables.
 */

void print_environment(void)
{
	char **env_var = environ;

	while (*env_var)
	{
		printf("%s\n", *env_var);
		env_var++;
	}
}

#include "shell.h"
/**
 * free_args - Free the memory allocated for an array of strings.
 * @args: The array of strings to free.
 */
void free_args(char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}

	free(args);
}

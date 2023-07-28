#include "shell.h"

/**
 * free_args - Free the memory allocated for an array of strings.
 * @args: The array of strings to free.
 */
void free_args(char **args)
{
	if (args == NULL)
		return;

	for (int i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
		args[i] = NULL;
	}


	free(args);
}

#include "shell.h"

/**
 * my_env - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}


/**
 * my_getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: environment variable name.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *my_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p + _strlen(name));
		node = node->next;
	}

	return (NULL);
}


/**
 * my_setenv - Initializes a new
 * environment variable or modifies an existing one.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (setenv(info->argv[1], info->argv[2], 1) == 0)
		return (0);

	_eputs("Error setting environment variable\n");
	return (1);
}


/**
 * my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_unsetenv(info_t *info)
{
	int arg_index;

	if (info->argc == 1)
	{
	_eputs("Too few arguments.\n");
	return (1);
	}

	for (arg_index = 1; arg_index < info->argc; arg_index++)
	unsetenv(info->argv[arg_index]);

	return (0);
}


/**
 * populate_env_list - Populates the env linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *env_list = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	add_node_end(&env_list, environ[i], 0);

	info->env = env_list;
	return (0);
}

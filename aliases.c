#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * handle_alias - Handle the alias built-in command.
 * @args: An array of strings containing arguments for the alias command.
 *
 * Return: None.
 */

void handle_alias(char **args)
{
	if (args[1] == NULL)
	{
		print_all_aliases();
	}
	else
	{
		char *name = args[1];
		char *value = args[2];

		Alias *alias = find_alias(name);

		if (alias != NULL)
		{
			free(alias->value);
			alias->value = strdup(value);
		}
		else
		{
			add_alias(name, value);
		}
	}
}

/**
 * find_alias - Find an alias by name.
 * @name: The name of the alias to find.
 *
 * Return: A pointer to the Alias structure if found, or NULL if not found.
 */

Alias *find_alias(const char *name)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

/**
 * add_alias - Add a new alias to the linked list.
 * @name: The name of the alias to add.
 * @value: The value of the alias to add.
 *
 * Return: None.
 */

void add_alias(const char *name, const char *value)
{
	Alias *new_alias = (Alias *)malloc(sizeof(Alias));

	if (!new_alias)
	{
		perror("malloc");
		return;
	}

	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = alias_list;

	alias_list = new_alias;
}

/**
 * print_all_aliases - Print all aliases in the format name='value'.
 *
 * Return: None.
 */

void print_all_aliases(void)
{
	Alias *current = alias_list;

	while (current != NULL)
	{
		printf("%s='%s'\n", current->name, current->value);
		current = current->next;
	}
}

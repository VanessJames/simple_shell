#include "shell.h"

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	size_t count = list_len(head);

	if (!head || count == 0)
		return (NULL);

	char **strs = malloc(sizeof(char *) * (count + 1));

	if (!strs)
		return (NULL);

	size_t i = 0;
	list_t *node = head;

	while (node)
	{
		strs[i] = _strdup(node->str);
		if (!strs[i])
		{
			for (size_t j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		node = node->next;
		i++;
	}

	strs[count] = NULL;
	return (strs);
}


/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(const char *path)
{
	struct stat st;

	if (!path || stat(path, &st) != 0)
		return (0);

	if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR
		|| st.st_mode & S_IXGRP || st.st_mode & S_IXOTH))
		return (1);

	return (0);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	while (*pp)
	{
		free(*pp);
		pp++;
	}

	free(a);
}

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
size_t _strlen(const char *s)
{
	size_t length = 0;

	if (!s)
		return (0);

	while (s[length] != '\0')
		length++;

	return (length);
}

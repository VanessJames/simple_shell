#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * append_path - Append a new directory to the PATH environment variable.
 * @path_list: The original PATH environment variable value.
 * @new_path: The directory to be appended to the PATH.
 *
 * Return: A new string containing the updated PATH, or NULL on failure.
 */
char *append_path(char *path_list, char *new_path)
{
	if (!path_list || !new_path)
	{
		return (NULL);
	}

	int path_list_len = strlen(path_list);
	int new_path_len = strlen(new_path);

	char *new_path_list = (char *)malloc(path_list_len + new_path_len + 2);

	if (!new_path_list)
	{
		perror("malloc");
		return (NULL);
	}

	strcpy(new_path_list, path_list);
	if (new_path_list[path_list_len - 1] != '/')
	{
		strcat(new_path_list, "/");
	}
	strcat(new_path_list, new_path);

	return (new_path_list);
}

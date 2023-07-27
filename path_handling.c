#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 * find_executable - Find the executable file
 * in the directories listed in PATH.
 * @command: The command to find the executable for.
 *
 * Return: A string containing the full
 * path to the executable, or NULL if not found.
 */
char *find_executable(char *command)
{
	char *path = getenv("PATH");
	char *dir, *path_copy, *executable;
	int command_len, dir_len, path_copy_len, executable_len;
	int i, j, found;

	if (!path || !command)
	{
		return (NULL);
	}
	command_len = strlen(command);
	path_copy_len = strlen(path) + 1;
	path_copy = (char *)malloc(path_copy_len);
	if (!path_copy)
	{
		perror("malloc");
		return (NULL);
	}
	strcpy(path_copy, path);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		dir_len = strlen(dir);
		executable_len = dir_len + command_len + 2;
		executable = (char *)malloc(executable_len);
	if (!executable)
	{
		perror("malloc");
		free(path_copy);
		return (NULL);
	}
	strcpy(executable, dir);
	strcat(executable, "/");
	strcat(executable, command);
	found = access(executable, X_OK);
	if (found == 0)
	{
		free(path_copy);
		return (executable);
	}
	free(executable);
	dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

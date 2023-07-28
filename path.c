#include "shell.h"

/**
 * find_executable - Find the full path of an executable in the PATH.
 * @command: The command to search for.
 *
 * Return: A pointer to the full path of the
 * executable if found, NULL otherwise.
 */
char *find_executable(char *command)
{
	char *path_env = getenv("PATH");
	char *path_copy, *dir, *full_path;
	int command_len, dir_len;

	if (!path_env)
		return (NULL);

	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);

	command_len = _strlen(command);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		dir_len = _strlen(dir);
	}
	full_path = (char *)malloc((dir_len + command_len + 2) * sizeof(char));
	if (!full_path)
	{
		free(path_copy);
		return (NULL);


		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}


#include "shell.h"
#include <limits.h>
#include <unistd.h>

/**
 * handle_exit - Handles the built-in exit command.
 * @status: The exit status to be returned.
 *
 * Description: This function takes an exit status as an argument and
 * exits the shell with the provided status. If the status is not
 * provided, it exits with a default status of 0.
 */

void handle_exit(char *status)
{
	int exit_status = (status != NULL) ? atoi(status) : 0;

	exit(exit_status);
}

/**
 * handle_cd - Handles the built-in cd command.
 * @directory: The directory to change to.
 *
 * Description: This function changes the current working directory
 * of the shell process to the specified directory. If no directory
 * is provided, it changes to the home directory.
 */

void handle_cd(char *directory)
{
	char *home_dir = getenv("HOME");
	char current_dir[PATH_MAX];

	if (directory == NULL)
	{
		if (home_dir)
			chdir(home_dir);
		else
			fprintf(stderr, "cd: No home directory found.\n");
	}
	else if (strcmp(directory, "-") == 0)
	{
		char *prev_dir = getenv("OLDPWD");

		if (prev_dir)
			chdir(prev_dir);
		else
			fprintf(stderr, "cd: No previous directory found.\n");
	}
	else
	{
		if (chdir(directory) != 0)
			perror("cd");
	}

        if (getcwd(current_dir, sizeof(current_dir)) != NULL)
        {
                setenv("PWD", current_dir, 1);
        }
}

/**
 * handle_env - Handles the built-in env command.
 *
 * Description: This function prints the current environment variables.
 */

void handle_env(void)
{
	extern char **environ;
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * handle_setenv - Handles the built-in setenv command.
 * @name: The name of the environment variable to set.
 * @value: The value to set for the environment variable.
 *
 * Description: This function sets the value of the specified environment
 * variable. If the variable does not exist, it is created. If the name
 * is NULL or empty, or the value is NULL, the function prints an error.
 */

void handle_setenv(char *name, char *value)
{
	if (name == NULL || name[0] == '\0' || value == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}

	if (setenv(name, value, 1) != 0)
	{
		perror("setenv");
	}
}

/**
 * handle_unsetenv - Handles the built-in unsetenv command.
 * @name: The name of the environment variable to unset.
 *
 * Description: This function unsets (removes) the specified environment
 * variable. If the name is NULL or empty, the function prints an error.
 */

void handle_unsetenv(char *name)
{
	if (name == NULL || name[0] == '\0')
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return;
	}

	if (unsetenv(name) != 0)
	{
		perror("unsetenv");
	}
}

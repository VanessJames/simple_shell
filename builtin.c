#include "shell.h"
#include <stdlib.h>
/*
 *Custom output function to replace putchar and printf
 */

void output(const char *str)
{
	while (*str)
	{
		write (1, str, 1);
		str++;
	}
}

/**
 * handle_exit - Handle the "exit" built-in shell command.
 * @arg: The argument passed to the "exit" command (optional).
 *
 * Description: This function handles the "exit" built-in shell command.
 * If no argument is provided, the function exits the shell with a
 * status of 0. If an argument is provided,
 * it is converted to an integer using the custom_atoi
 * function, and the shell exits with the specified exit status.
 *
 * @arg: The argument passed to the "exit" command.
 * If NULL, the shell exits with status 0.
 * If a valid integer string, the shell exits with the specified integer value.
 */

void handle_exit(char *arg)
{
	int exit_status;

	if (arg == NULL)
	{
		exit(0);
	}

	exit_status = atoi(arg);
	exit(exit_status);

}

/**
 * handle_env - Handle the "env" built-in shell command.
 *
 * Description: This function handles the "env" built-in shell command.
 * It prints the current environment variables to standard output,
 * each on a new line.
 */
void handle_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		output(*env);
		output("\n");
		env++;
	}
}

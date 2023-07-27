#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/* The get_exit_status() function implementation here */
/* ... */

/**
 * get_pid - Get the current process ID as a string.
 *
 * Return: A new string containing the process ID, or NULL on failure.
 */
char *get_pid(void)
{
	char *pid_str = NULL;
	int pid = getpid();

	int num_digits = 1;
	int temp = pid;

	while (temp >= 10)
	{
		num_digits++;
		temp /= 10;
	}

	pid_str = (char *)malloc(num_digits + 1);
	if (!pid_str)
	{
		perror("malloc");
		return (NULL);
	}

	snprintf(pid_str, num_digits + 1, "%d", pid);

	return (pid_str);
}

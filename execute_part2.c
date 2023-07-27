#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * wait_for_child - Wait for a child process to complete.
 * @pid: The process ID of the child process.
 *
 * Return: 0 on success, or 1 on failure.
 */

int wait_for_child(pid_t pid)
{
	int status;

	do {
		if (waitpid(pid, &status, WUNTRACED) == -1)
		{
			perror("waitpid");
			return (1);
		}
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));

	return ((WIFEXITED(status)) ? WEXITSTATUS(status) : (1));
}

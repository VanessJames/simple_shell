#include "shell.h"

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		char *num_str = convert_number(h->num, 10, 0);
		if (num_str)
		{
			_puts(num_str);
			_free(num_str);
		}

		_putchar(':');
		_putchar(' ');

		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}

	return (i);
}


/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer, or NULL if an error occurs
 */
char *dup_chars(const char *pathstr, int start, int stop)
{
    if (!pathstr || start < 0 || stop < 0 || start >= stop)
        return N(ULL);

    int len = stop - start;
    char *buf = (char *)malloc((len + 1) * sizeof(char));
    if (!buf)
        return (NULL);

    int k = 0;
    for (int i = start; i < stop; i++)
    {
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    }
    buf[k] = '\0';
    return (buf);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block or NULL on failure.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}


/**
 * fork_cmd - forks a new process and executes a command
 * @cmd: the command to be executed
 * @argv: the argument vector
 * @envp: the environment variables
 *
 * Return: void
 */
void fork_cmd(const char *cmd, char *const argv[], char *const envp[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork_cmd - fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		execve(cmd, argv, envp);

		perror("fork_cmd - execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("fork_cmd - wait");
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);

			if (exit_status == 126)
				fprintf(stderr, "%s: Permission denied\n", cmd);


			exit(exit_status);
		}
	}
}

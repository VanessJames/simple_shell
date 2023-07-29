#include "shell.h"
#include <stdio.h>
#include <signal.h>


/**
 * my_strncpy - copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 * Return: The concatenated string.
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}


/**
 * my_input_buf - buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of len var.
 *
 * Return: Bytes read.
 */
ssize_t my_input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t buffer_size = 0;

	if (*len == 0)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		#if USE_GETLINE
			read_bytes = getline(buf, &buffer_size, stdin);
		#else
			read_bytes = my_getline(info, buf, &buffer_size);
		#endif
	if (read_bytes > 0)
	{
		if ((*buf)[read_bytes - 1] == '\n')
		{
			(*buf)[read_bytes - 1] = '\0';
			read_bytes--;
		}
		info->linecount_flag = 1;
		my_remove_comments(*buf);
		build_history_list(info, *buf, info->histcount++);
		if (my_strchr(*buf, ';'))
		{
			*len = read_bytes;
			info->cmd_buf = buf;
		}
	}
	}
	return (read_bytes);
}

/**
 * my_input_buf - buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of len var.
 *
 * Return: Bytes read.
 */
ssize_t my_input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t buffer_size = 0;

	if (*len == 0)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		#if USE_GETLINE
		read_bytes = getline(buf, &buffer_size, stdin);
		#else
		read_bytes = my_getline(info, buf, &buffer_size);
		#endif

		if (read_bytes > 0)
		{
			if ((*buf)[read_bytes - 1] == '\n')
			{
				(*buf)[read_bytes - 1] = '\0';
				read_bytes--;
			}
			info->linecount_flag = 1;
			my_remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			if (my_strchr(*buf, ';'))
			{
				*len = read_bytes;
				info->cmd_buf = buf;
			}
		}
	}
	return (read_bytes);
}
/**
 * my_read_buf - reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Pointer to the size.
 *
 * Return: r.
 */
ssize_t my_read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i == 0)
	{
		r = read(info->readfd, buf, READ_BUF_SIZE);
		if (r >= 0)
		*i = (size_t)r;
	}
	return (r);
}
/**
 * sigintHandler - signal handler for SIGINT (Ctrl+C)
 * @sig_num: the signal number (unused)
 *
 * Return: void
 */
void sigintHandler(int sig_num)
{
	(void)sig_num;

	putchar('\n');
	printf("$ ");
	fflush(stdout);
}

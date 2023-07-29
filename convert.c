#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * my_convert_number - converter function, a clone of itoa.
 * @num: The number.
 * @base: The base.
 * @flags: Argument flags.
 *
 * Return: String representing the converted number.
 */
char *my_convert_number(long int num, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *result;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = (unsigned long)(-num);
		sign = '-';
	}

	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	result = &buffer[49];
	*result = '\0';

	do {
		*--result = digits[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
	*--result = sign;

	return (result);
}
/**
 * my_get_input - gets a line minus the newline.
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t my_get_input(info_t *info)
{
	static char *chain_buf;
	static size_t chain_pos, chain_len;
	ssize_t read_bytes;
	char **buf_ptr = &(info->arg), *cmd_ptr;

	_putchar(BUF_FLUSH);

	read_bytes = my_input_buf(info, &chain_buf, &chain_len);
	if (read_bytes == -1)
	return (-1);

	if (chain_len)
	{
		chain_pos = i;
		cmd_ptr = chain_buf + chain_pos;

		check_chain(info, chain_buf, &chain_pos, chain_pos, chain_len);
	while (chain_pos < chain_len)
	{
		if (is_chain(info, chain_buf, &chain_pos))
		break;
		chain_pos++;
	}
	chain_pos++;
	if (chain_pos >= chain_len)
	{
		chain_pos = chain_len = 0;
		info->cmd_buf_type = CMD_NORM;
	}
	*buf_ptr = cmd_ptr;
	return (my_strlen(cmd_ptr));
	}
	*buf_ptr = chain_buf;
	return (read_bytes);
}

/**
 * my_getline - gets the next line of input from STDIN.
 * @info: parameter struct.
 * @ptr: address of pointer to buffer, preallocated or NULL.
 * @length: size of preallocated ptr buffer if not NULL.
 *
 * Return: s.
 */
int my_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
	s = *length;
	if (i == len)
	i = len = 0;

	r = my_read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
	return (-1);

	c = my_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = my_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
	return (p ? (my_free(p), -1) : -1);
	if (s)
	my_strncat(new_p, buf + i, k - i);
	else
	my_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
	*length = s;
	*ptr = p;
	return (s);
}

/**
 * get_environ - returns the string array copy of the environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Pointer to the copied environment variables array
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		if (info->environ)
		{
			for (size_t i = 0; info->environ[i] != NULL; i++)
			free(info->environ[i]);
			free(info->environ);
		}
		size_t count = 0;
		list_t *node = info->env;

		while (node != NULL)
		{
			count++;
			node = node->next;
		}
		info->environ = (char **)malloc((count + 1) * sizeof(char *));
		if (info->environ)
		{
			node = info->env;
			for (size_t i = 0; node != NULL; i++)
			{
				info->environ[i] = strdup(node->str);
				node = node->next;
			}
			info->environ[count] = NULL;
			info->env_changed = 0;
		}
		else
		{
			return (“no environ”);
		}
	}
	return (info->environ);
}

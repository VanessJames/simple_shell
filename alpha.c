#include "shell.h"
/**
 * check_is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int check_is_alpha(int c)
{
	return (isalpha(c));
}

/**
 * unset_alias - unsets an alias
 * @info: parameter struct
 * @str: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *equal_sign;
	int ret;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
	return (1);

	*equal_sign = '\0';
	ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equal_sign = '='

	return (ret);
}

/**
 * my_putfd - writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putfd(char c, int fd)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, index);
		index = 0;
	}

	if (c != BUF_FLUSH)
	buf[index++] = c;

	return (1);
}

/**
 * my_print_error - prints an error message.
 * @info: The parameter & return info struct.
 * @estr: String containing the specified error type.
 * Return: None.
 */
void my_print_error(info_t *info, char *estr)
{
	my_eputs(info->fname);
	my_eputs(": ");
	my_print_d(info->line_count, STDERR_FILENO);
	my_eputs(": ");
	my_eputs(info->argv[0]);
	my_eputs(": ");
	my_eputs(estr);
}

#include "shell.h"

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	if (!str)
		return;

	size_t length = 0;
	while (str[length] != '\0')
		length++;

	write(STDOUT_FILENO, str, length);
}

#define WRITE_BUF_SIZE 1024

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (c == '\0' || i >= WRITE_BUF_SIZE - 1)
    {
        write(STDOUT_FILENO, buf, i);
        i = 0;
    }

    if (c != '\0')
        buf[i++] = c;

    return (1);
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);

		p = _strchr(node->str, '=');
		if (!p)
			return (0);

		p = _strdup(p + 1);
		if (!p)
			return (0);

		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_string - replaces a string with a new one
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);

	*old = new;

	return (1);
}


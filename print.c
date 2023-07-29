#include "shell.h"

/**
 * my_print_d - function prints a decimal (integer) number (base 10).
 * @input: The input.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int my_print_d(int input, int fd)
{
	int (*print_char)(char) = my_putfd;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
	print_char = my_eputchar;

	if (input < 0)
	{
		abs_value = (unsigned int)(-input);
		print_char('-');
		count++;
	}
	else
	{
		abs_value = (unsigned int)input;
	}

	current = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			print_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char('0' + current);
	count++;

	return (count);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property
 *
 * Return: 1 if variable was removed, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *current = info->env;
	list_t *prev = NULL;
	int removed = 0;

	if (!current || !var)
	return (0);

	while (current)
	{
	char *p = starts_with(current->str, var);

	if (p && *p == '=')
	{
		if (prev == NULL)
		{
			info->env = current->next;
		}
		else
		{
			prev->next = current->next;
		}
		free(current->str);
		free(current);
		current = prev ? prev->next : info->env;
		removed = 1;
		continue;
	}
	prev = current;
	current = current->next;
	}
	if (removed)
	info->env_changed = 1;

	return (removed);
}

/**
 * _setenv - Initialize a new environment variable,
 *           or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property
 * @value: The string env var value
 *
 * Return: 0 on success, 1 on error
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
	return (1);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
	return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	info->env_changed = 1;
	return (0);
}

/**
 * clear_info - initializes info_t struct
 * @info: Pointer to the struct to be cleared
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

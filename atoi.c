#include “shell.h”
/**
 * custom_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int custom_atoi(const char *s)
{
	int i, sign = 1, flag = 0;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
		sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		flag = 2;
	}

	return (sign == -1 ? -result : result);
}
/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_cd(info_t *info)
{
	char *target_dir;
	char buffer[1024];
	int chdir_ret;

	if (!info->argv[1] || _strcmp(info->argv[1], "~") == 0)
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
		target_dir = _getenv(info, "PWD=");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		target_dir = _getenv(info, "OLDPWD=");
		if (!target_dir)
		{
			_puts("cd: OLDPWD not set\n");
			return (1);
		}
	}
	else
	{
		target_dir = info->argv[1];
	}
	chdir_ret = chdir(target_dir);

	if (chdir_ret == -1)
	{
		print_error(info, "cd: ");
		_eputs(target_dir);
		_eputchar(':');
		_eputchar(' ');
		perror("");
		return (1);
	}

	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, 1024));

	return (0);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;

	if (info->argc == 1)
	{
		list_t *node = info->alias;

		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
		set_alias(info, info->argv[i]);
		else
		print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
/**
 * my_eputs - prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void my_eputs(char *str)
{
	int index = 0;

	if (!str)
	return;

	while (str[index] != '\0')
	{
		my_eputchar(str[index]);
		index++;
	}
}

/**
 * my_eputchar - writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_eputchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
	buf[index++] = c;
	return (1);
}

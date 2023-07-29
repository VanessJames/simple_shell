#include "shell.h"
/**
 * check_interactive_mode - determines
 * if shell is activated in interactive mode.
 * @info: the info_t struct's pointer
 *
 * Return: 1 if the mode is interactive; 0 otherwise
 */
int check_interactive_mode(info_t *info)
{
	int stdin_fileno = STDIN_FILENO
	int read_fd = info->readfd;

	int is_interactive = isatty(stdin_fileno) && read_fd <= 2;

	return (is_interactive);
}


/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments.
 * Return: exits with a given exit status
 * (0) if info->argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int exit_status = 0;

	if (info->argv[1])
	{
		char *endptr;
		long int exit_code = strtol(info->argv[1], &endptr, 10);

		if (*endptr != '\0')
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		exit_status = (int)exit_code;
	}

	info->err_num = exit_status;
	return (-2);
}


/**
 * my_help - displays help information for the shell commands
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("This is a custom shell implementation.\n");
	_puts("Supported commands:\n");
	_puts("  cd [DIRECTORY]  Change the current directory.\n");
	_puts("  exit [STATUS]   Exit the shell with an optional status.\n");
	_puts("  help            Display help information.\n");
	_puts("  [COMMAND]       Execute an external command or built-in command.\n");
	return (0);
}


/**
 * my_erratoi - converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in the string, the converted number otherwise,
 *         -1 on error.
 */
int my_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
	s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
			return (-1);
		}
		else
			return (-1);
	}
	return ((int)result);
}


/**
 * my_putsfd - prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int my_putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
	return (0);
	while (*str)
	{
		char_count += my_putfd(*str++, fd);
	}
	return (char_count);
}

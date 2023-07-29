#include "shell.h"

/**
 * set_info - initializes info_t struct
 * @info: Pointer to the struct to be initialized
 * @av: Argument vector (array of strings)
 */
void set_info(info_t *info, char **av)
{
	int i;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (i = 0; info->argv && info->argv[i]; i++)
			;

		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}



/**
 * free_info - frees info_t struct fields
 * @info: Pointer to the struct to be freed
 * @all: True if freeing all fields, false otherwise
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		free_list(&(info->env));
		free_list(&(info->history));
		free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}



/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: Allocated string containing the history file path,
 *         or NULL if an error occurs.
 */
char *get_history_file(info_t *info)
{
	char *buf = NULL;
	char *dir = _getenv(info, "HOME=");

	if (!dir)
		return (NULL);

	size_t buf_size = _strlen(dir) + _strlen(HIST_FILE) + 2;

	buf = malloc(sizeof(char) * buf_size);

	if (!buf)
		return (NULL);

	_snprintf(buf, buf_size, "%s/%s", dir, HIST_FILE);
	return (buf);
}



/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	FILE *file;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file = fopen(filename, "w");
	free(filename);

	if (!file)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		fputs(node->str, file);
		fputc('\n', file);
	}

	fclose(file);
	return (1);
}


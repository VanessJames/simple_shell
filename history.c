#include “shell.h”
/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	FILE *file;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	file = fopen(filename, "r");
	free(filename);
	if (!file)
		return (0);
	if (fseek(file, 0, SEEK_END) != 0)
	{
		fclose(file);
		return (0);
	}
	long fsize = ftell(file);

	if (fsize <= 0)
	{
		fclose(file);
		return (0);
	}
	rewind(file);
	buf = malloc(fsize + 1);
	if (!buf)
	{
		fclose(file);
		return (0);
	}
	size_t rdlen = fread(buf, 1, fsize, file);

	if (rdlen <= 0)
	{
		fclose(file);
		free(buf);
		return (0);
	}
	buf[rdlen] = '\0';
	fclose(file);

	for (i = 0; i < rdlen; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	if (buf == NULL)
		return (0);

	list_t *new_node = create_node(buf);

	if (new_node == NULL)
		return (0);

	new_node->linecount = linecount;

	if (info->history == NULL)
	{
		info->history = new_node;
	}
	else
	{
		list_t *node = info->history;

		while (node->next)
			node = node->next;
		node->next = new_node;
	}

	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->linecount = i++;
		node = node->next;
	}
	info->histcount = i;
	return (i);
}

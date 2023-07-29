#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info;
	int fd = 2;

	info_init(&info);

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			handle_file_open_error(av[0], av[1]);
			return (EXIT_FAILURE);
		}
		info.readfd = fd;
	}

	populate_env_list(&info);

	read_history(&info);

	hsh(&info, av);

	cleanup(&info);
	return (EXIT_SUCCESS);
}

/**
 * info_init - initializes the info_t struct with default values
 * @info: pointer to the info_t struct to initialize
 */
void info_init(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
	info->environ = NULL;
	info->cmd_buf = NULL;
	info->cmd_buf_type = CMD_NORM;
	info->readfd = 0;
	info->history = NULL;
	info->alias = NULL;
	info->linecount_flag = 0;
	info->env = NULL;
	info->histcount = 0;
	info->env_changed = 0;
	info->prompt = NULL;
	info->fname = NULL;
}

/**
 * handle_file_open_error - handles error when opening a file
 * @prog_name: name of the program
 * @filename: name of the file that couldn't be opened
 */
void handle_file_open_error(const char *prog_name, const char *filename)
{
	if (errno == EACCES)
		exit_with_error(prog_name, filename, "Permission denied", 126);
	if (errno == ENOENT)
		exit_with_error(prog_name, filename, "File not found", 127);
	exit_with_error(prog_name, filename, "Unknown error", EXIT_FAILURE);
}

/**
 * exit_with_error - prints an error message and exits with the specified code
 * @prog_name: name of the program
 * @filename: name of the file causing the error
 * @message: error message
 * @exit_code: exit code to be used in the exit call
 */
void exit_with_error(const char *prog_name, const char *filename, const char *message, int exit_code)
{
	_eputs(prog_name);
	_eputs(": 0: Can't open ");
	_eputs(filename);
	_eputs(": ");
	_eputs(message);
	_eputchar('\n');
	_eputchar(BUF_FLUSH);
	exit(exit_code);
}

/**
 * cleanup - frees allocated memory and performs cleanup before exiting
 * @info: pointer to the info_t struct to cleanup
 */
void cleanup(info_t *info)
{
	free_list(&(info->history));
	free_list(&(info->alias));
	free_list(&(info->env));
	free_info(info, 1);
}


#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH (-1)

/* Structures */

/**
 * struct list_s - singly linked list structure
 * @str: the stored string
 * @num: node index used by history
 * @next: points to the next node
 */
typedef struct list_s
{
	char *str;
	int num;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - struct for built-in commands
 * @type: the command type
 * @func: function pointer to the built-in command
 */
typedef struct builtin_s
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/**
 * struct info_s - parameter and return info struct
 * @argc: the argument count
 * @argv: the argument vector
 * @env: environment
 * @status: last command exit status
 * @history: command history list
 * @alias: alias list
 * @path: path to the command
 * @cmd_buf_type: type of command buffer (e.g., CMD_OR, CMD_AND, CMD_CHAIN)
 * @line_count: the command line count for history
 * @linecount_flag: a flag to set line count
 * @readfd: read file descriptor for non-interactive mode
 * @interactive: interactive mode flag
 * @err_num: error number to exit with
 */
typedef struct info_s
{
	int argc;
	char **argv;
	char **env;
	int status;
	list_t *history;
	list_t *alias;
	char *path;
	int cmd_buf_type;
	size_t line_count;
	int linecount_flag;
	int readfd;
	int interactive;
	int err_num;
} info_t;

/* Function Prototypes */

char *_getenv(info_t *info, const char *name);
char **get_environ(info_t *info);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
size_t _strlen(char *s);
char *_strcat(char *dest, char *src);
void _puts(char *str);
int _putchar(char c);
void _eputs(char *str);
void _eputchar(char c);
int _memset(char *s, char b, unsigned int n);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *h);
void free_info(info_t *info, int status);
void read_history(info_t *info);
void write_history(info_t *info);
int is_delim(char c, char *delim);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int is_chain(info_t *info, char *buf, size_t *p);
int interactive(info_t *info);
void print_error(info_t *info, char *message);
int replace_alias(info_t *info);
int replace_string(char **old, char *new);
void fork_cmd(info_t *info);
void find_cmd(info_t *info);
char *find_path(info_t *info, char *pathstr, char *cmd);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
int find_builtin(info_t *info);
int shell_loop(info_t *info, char **av);
void populate_env_list(info_t *info);
ssize_t get_input(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

#endif /* SHELL_H */

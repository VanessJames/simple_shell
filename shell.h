#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Global Variables */
extern char **environ;

/* Function Prototypes */

/* main.c */
int main_loop(void);

/* prompt.c */
void display_prompt(void);

/* getline.c */
char **parse_command_line(char *line);
void free_args(char **args);

/* command_handling.c */
int execute_command(char *command);

/* execute_part1.c */
int execute_command(char *command);

/* execute_part2.c */
int wait_for_child(pid_t pid);

/* builtin_part1.c */
int is_builtin(char *command);

/* builtin_part2.c */
int execute_builtin(char **args);

typedef struct Alias Alias;
Alias *find_alias(const char *name);
void add_alias(const char *name, const char *value);
void print_all_aliases(void);
void handle_alias(char **args);

/* Move the struct definition and typedef here */
typedef struct alias_node {
    char *name;
    char *value;
    struct alias_node *next;
} alias_node_t;

extern alias_node_t *aliases;

/* logical_operators_part1.c */
int handle_logical_operators(char *command_line);

/* logical_operators_part2.c */
int handle_logical_operators_part2(char *command_line);

/* path_handling_part1.c */
char *find_executable(char *command);

/* path_handling_part2.c */
char *append_path(char *path_list, char *new_path);

/* variables_part1.c */
char *replace_variables(char *command_line);

/* variables_part2.c */
char *get_pid(void);

#endif /* SHELL_H */

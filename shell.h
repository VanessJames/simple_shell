#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/* Function prototypes*/

/* Helper functions in helper.c*/
char **split_input(char *input);
char *get_next_arg(char **input);
void free_args(char **args);

/* Built-in commands in shell.c*/
void print_environment(void);

/* Core shell functions in shell.*/
void display_prompt(void);
int execute_command(char **args);
void execute_command_line(char *input);

#endif /* SHELL_H */

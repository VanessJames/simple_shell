#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 100
#define MAX_ENV_VARIABLES 100
#define BUFFER_SIZE 1024


/* Function prototypes */
ssize_t custom_getline(char *line, size_t size);
void parse_input(char *input, char **tokens);
int execute_command(char *command, char **args);
int handle_builtin(char *command, char **args);
void handle_exit(char *arg);
void handle_cd(char *arg);
void handle_env();
void handle_setenv(char *variable, char *value);
void handle_unsetenv(char *variable);
void interactive_shell_loop(void);
void print_prompt(void);
void interactive_shell_loop(void);
void process_command(char *input);
void free_tokens(char **tokens);

#endif /* SHELL_H */


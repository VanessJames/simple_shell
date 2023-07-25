#ifdef SHELL_H
#define SHELL_H

#define MAX_INPUT_LENGHT 1024
#define MAX_TOKENS 64
#define DELIMITER "\t\r\n\a"
#define BEFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
include <stddef.h>

/* The Function prototypes for each file */
int main (void);
void parse_input(char *input, char *tokens[]);
int execute_command(char *command, char *args[]);
void handle_exit(void);
void handle_env(void);

/* External declaration for environ variable */
extern char **environ;

#endif 

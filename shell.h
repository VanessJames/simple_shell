#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Constants */
#define TOKEN_BUFSIZE 64
#define SHELL_EXIT 1

/* Global Variable */
extern char **environ;

/* Function Prototypes */
char *display_prompt(void);
char **parse_line(char *line);
int execute_command(char **args);
int is_builtin(char *command);
int execute_builtin(char **args);
void print_environment(void);
char *find_executable(char *command);
size_t _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
void free_args(char **args);
char *_getenv(const char *name);

#endif /* SHELL_H */

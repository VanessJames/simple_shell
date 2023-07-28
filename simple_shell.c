#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * print_prompt - Print the shell prompt.
 */
void print_prompt(void)
{
	printf("$ ");
}

/**
 * read_command - Read the user input command.
 * @buffer: Buffer to store the user input.
 * Return: Number of characters read (excluding null ter*/
int read_command(char *buffer)
{
	int n_read;
	n_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	if (n_read == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	return (n_read);
}

/**
 * execute_command - Execute the user input command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		if (execlp(command, command, NULL) == -1)
	{
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	}
	else
	{

		wait(&status);
	}
}

/**
 * main - Entry point of the shell program.
 * Return: Always 0.
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	int n_read;

	while (1)
	{
		print_prompt();
		n_read = read_command(buffer);

	if (n_read == 0)
	{
		printf("\n");
		break;
	}

	buffer[n_read - 1] = '\0';

	execute_command(buffer);
	}

	return (EXIT_SUCCESS);
}

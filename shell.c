#include "shell.h"
#include <stdio.h>

static char buffer[BUFFER_SIZE];
static int buffer_pos;
static int buffer_size;

/**
 * custom_getline - Read a line from standard input.
 * @line: The buffer to store the read line.
 * @size: The size of the buffer.
 *
 * Description: This function reads a line from standard input using a buffer.
 * It calls the least possible the read system call to fill the buffer.
 *
 * Return: The number of characters read (including the newline character),
 * -1 on failure or when encountering the end of file (Ctrl+D).
 */
static ssize_t custom_getline(char *line, size_t size)
{
	ssize_t read_bytes = 0;
	ssize_t i;

	while (1)
	{
		if (buffer_pos == buffer_size)
		{
			/* Buffer is empty, read from standard input*/
			buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (buffer_size <= 0)
			/* Error or end of file (Ctrl+D)*/
				return (-1);
			buffer_pos = 0;
		}

	for (i = buffer_pos; i < buffer_size && read_bytes < (ssize_t)(size - 1); i++)
	{
		if (buffer[i] == '\n')
		{
			/* Found newline, include it in the line and terminate*/
			line[read_bytes] = '\n';
			line[read_bytes + 1] = '\0';
			buffer_pos = i + 1;
			return (read_bytes + 1);
		}
		else
		{
			line[read_bytes++] = buffer[i];
		}
	}

		buffer_pos = buffer_size;
	}

	line[read_bytes] = '\0';
	return (read_bytes);
}

/**
 * process_command - Process and execute a command.
 * @input: The user input string containing the command.
 *
 * Description: This function takes the user input string, tokenizes it, and
 * executes the appropriate command based on the input provided.
 */

static void process_command(char *input)
{
	char *tokens[MAX_TOKENS];

	parse_input(input, tokens);

	if (tokens[0] != NULL)
	{
		/* Handle exit built-in command*/
		if (strcmp(tokens[0], "exit") == 0)
		{
			handle_exit(tokens[1]);
		}
		/* Handle env built-in command*/
		else if (strcmp(tokens[0], "env") == 0)
		{
			handle_env();
		}
		/* Execute other commands*/
		else
		{
			if (!execute_command(tokens[0], tokens))
			{
				fprintf(stderr, "Command not found: %s\n", tokens[0]);
			}
		}
	}
}

/**
 * interactive_shell_loop - Run the interactive shell loop.
 *
 * Description: This function initializes the interactive shell loop,
 * displaying
 * the shell name at startup, and continuously waits for user input.
 * It reads user input using the custom_getline function, parses the
 * input into tokens, and then processes and executes the commands
 * based on the input provided by the user.
 */

static void interactive_shell_loop(void)
{
	ssize_t bytes_read;
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("(Vaness&Jessica's Shell) "); /* Display the prompt*/

		/* Read user input*/
		bytes_read = custom_getline(input, MAX_INPUT_LENGTH);

		if (bytes_read == -1)
		{
			printf("\n"); /* Handle end of file (Ctrl+D)*/
			break;
		}

		input[bytes_read - 1] = '\0';
		process_command(input);
	}
}

/**
 * main - Entry point of the shell program.
 *
 * Description: This function initializes the interactive shell loop,
 * displaying the shell name at startup and continuously
 * waits for user input. It reads user input using the
 * custom_getline function, parses the input into tokens,
 * and then executes the appropriate commands based on the
 * input provided by the user.
 *
 * Return: Always returns 0.
 */

int main(void)
{
	printf("Welcome to Vaness&Jessica's Shell!\n");
	interactive_shell_loop();

	return (0);
}

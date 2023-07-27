#include "shell.h"
#include <stdio.h>
#include <unistd.h>


/**
 * interactive_shell_loop - Run the interactive shell loop.
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

void interactive_shell_loop(void)
{
	ssize_t bytes_read;
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf("(Vaness&Jessica's Shell) "); /* Display the prompt */

 		/* Read user input */
		bytes_read = read(STDIN_FILENO, input, MAX_INPUT_LENGTH);

		if (bytes_read == -1)
		{
			printf("\n"); /* Handle end of file (Ctrl+D) */
			break;
		}

		input[bytes_read - 1] = '\0'; /* Remove the newline character */
		process_command(input);/* Process and execute the command */
		/* TODO: Implement this part later */
	}
}

/**
 * process_command - Process and execute a command.
 * @input: The user input string containing the command.
 *
 * Description: This function takes the user input string,
 * tokenizes it, and executes the appropriate
 * command based on the input provided.
 */

void process_command(char *input)
{
	char *tokens[MAX_TOKENS];

	parse_input(input, tokens);

	if (tokens[0] != NULL)
	{
		/*Handle exit built-in command*/
		if (strcmp(tokens[0], "exit") == 0)
		{
			if (tokens[1] != NULL)
		{
			handle_exit(tokens[1]);
		}
		else
		{
			handle_exit(NULL);
		}
	}
 	/* Handle cd built-in command*/
	else if (strcmp(tokens[0], "cd") == 0)
	{
		handle_cd(tokens[1]);
	}
        /* Handle env built-in command*/
	else if (strcmp(tokens[0], "env") == 0)
	{
		handle_env();
	}
	/* Handle setenv built-in command */
	else if (strcmp(tokens[0], "setenv") == 0)
	{
		status = handle_setenv(tokens[1], tokens[2]);
	}
	/* Handle unsetenv built-in command */
	else if (strcmp(tokens[0], "unsetenv") == 0)
	{
		status = handle_unsetenv(tokens[1]);
	}
	/* Handle other commands */
	else
	{
		/* Check if the command contains logical operators */
		int i = 0;
	int skip_next_command = 0;

	while (tokens[i] != NULL)
	{
		if (strcmp(tokens[i], "&&") == 0)
		{
			if (tokens[i + 1] != NULL)
			{
 				int exit_status = execute_command
					(tokens[i - 1], tokens + i - 1);

				if (exit_status == 0)
				{
					skip_next_command = 1;
				}
				}
			}
				else if (strcmp(tokens[i], "||") == 0)
				{
					if (tokens[i + 1] != NULL)
					{
						int exit_status = execute_command
							(tokens[i - 1], tokens + i - 1);

				if (exit_status != 0)
				{
					skip_next_command = 1;
				}
			}
		}
			else if (!skip_next_command)
			{
				if (!execute_command(tokens[i], tokens + i))
				{
					fprintf(stderr, "Command not found: %s\n", tokens[i]);
				}
			}
			else
				{
                		    skip_next_command = 0;
                		}
                		i++;
			}
  		}
 	}
}

/**
 * main - Entry point of the shell program.
 *
 * Description: This function initializes the
 * interactive shell loop,
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

#include <stdio.h>
#include <string.h>
#include "shell.h"

/**
 * handle_logical_operators_part2 - Continue handling
 * logical operators in the command line.
 * @command_line: The command line with logical operators to be handled.
 *
 * Return: 0 on success, or 1 on failure.
 */

int handle_logical_operators_part2(char *command_line)
{
	char *token;
	const char *delimiters = "&&||";
	int result = 1;
	int prev_status = 1;

	while (*trimmed_token == ' ' || *trimmed_token == '\t')
	{
		trimmed_token++;
	}
	int token_len = strlen(trimmed_token);

	while (token_len > 0 && (trimmed_token[token_len - 1]
		== ' ' || trimmed_token[token_len - 1] == '\t'))
	{
		trimmed_token[--token_len] = '\0';
	}


	if (strcmp(trimmed_token, "||") == 0)
	{
		if (prev_status != 0)
		{
			result = execute_command(strtok(NULL, delimiters));
		}
	}
	else
	{
		result = execute_command(trimmed_token);
	}

	if (result != 0)
	{
		prev_status = 1;
	}
	else
	{
		prev_status = 0;
	}

		token = strtok(NULL, delimiters);
	}

	return (result);
}

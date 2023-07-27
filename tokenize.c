#include "shell.h"

/**
 * parse_input - Split the input string into tokens.
 * @input: The user input string containing the command.
 * @tokens: An array of strings to store the tokens.
 *
 * Description: This function takes the user input
 * string and tokenizes it
 * based on spaces and stores the tokens in the 'tokens' array.
 */

void parse_input(char *input, char **tokens)
{
	char *token;
	int index = 0;

	/* Tokenize the input based on spaces */
	token = strtok(input, " \t\n");

	/* Store tokens in the tokens array */
	while (token != NULL)
	{
		tokens[index] = token;
		index++;
		token = strtok(NULL, " \t\n");
	}

	tokens[index] = NULL;
}

/**
 * free_tokens - Free the memory allocated for an array of tokens.
 * @tokens: The array of tokens to be freed.
 *
 * Description: This function frees the memory
 * allocated for an array of tokens.
 * The array of tokens must have been previously
 * created using the tokenize_input function.
 * After freeing the memory for each token, the
 * orresponding element in the array is set to NULL.
 * Finally, the memory allocated for the tokens array itself is freed.
 */
void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i] != NULL; i++)
	{
		free(tokens[i]);
	}

	free(tokens);
}

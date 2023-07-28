#include "shell.h"

/**
 * parse_input_helper - Parse input into tokens using strtok.
 * @input: The input string to be parsed.
 * @tokens: An array to store the parsed tokens.
 * @num_tokens: A pointer to an integer to store the number of tokens.
 *
 * Description: This function takes an input string and tokenizes it using
 * strtok with a delimiter. The parsed tokens are stored in the
 * tokens array, and the number of tokens is stored in the num_tokens
 * variable.
 */

static void parse_input_helper(char *input, char *tokens[], int *num_tokens)
{
	char *token;
	*num_tokens = 0;
	token = strtok(input, DELIMITER);

	while (token != NULL && *num_tokens < MAX_TOKENS - 1)
	{
		tokens[(*num_tokens)++] = token;
		token = strtok(NULL, DELIMITER);
	}
	tokens[*num_tokens] = NULL;
}

/**
 * parse_input - Parse input into tokens.
 * @input: The input string to be parsed.
 * @tokens: An array to store the parsed tokens.
 *
 * Description: This function is a wrapper for parse_input_helper. It takes an
 * input string and tokenizes it using parse_input_helper. The
 * parsed tokens are stored in the tokens array.
 */

void parse_input(char *input, char *tokens[])
{
	int num_tokens;

	parse_input_helper(input, tokens, &num_tokens);
}

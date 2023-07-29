#include "shell.h"

/**
 * my_remove_comments - function replaces the first instance of '#' with '\0'.
 * @str: Address of the string to modify.
 *
 * Return: Always 0.
 */
void my_remove_comments(char *str)
{
	if (!str)
	return;
	char *comment_start = strstr(str, "#");

	if (comment_start && (comment_start == str || *(comment_start - 1) == ' '))
	{
		*comment_start = '\0';
	}
}

/**
 * my_strncat - concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The number of bytes to be maximally used.
 * Return: The concatenated string.
 */
char *my_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}
		dest[dest_len + i] = '\0';
		return (dest);
}

/**
 * my_strchr - locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the memory areas
 * containing the character, or NULL if not found.
 */
char *my_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
		return (char *s);
		s++;
	}
	if (c == '\0')
	return (char *s);
	return (NULL);
}

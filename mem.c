#include "shell.h"

/**
 * bfree - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 *
 * Description: The memory pointed to by the pointer
 * is freed, and the pointer is set to NULL. This
 * function has no effect if the pointer is already NULL.
 */
void bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}


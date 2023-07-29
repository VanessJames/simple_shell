#include "shell.h"

/**
 * add_node - adds a node to the list's beginning
 * @str: str field of node
 * @num: History makes use of a node index.
 * @head: address of the reference to the head node
 *
 * Return: the address of the new head node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node = NULL;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	new_node->str = NULL;
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of the reference to the head node
 * @num: history uses a node index
 * @str: node str field
 *
 * Return: the address of the new node added to the end of the list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *last_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	new_node->str = NULL;
	new_node->num = num;
	new_node->next = NULL;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (*head)
	{
		last_node = *head;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * print_list_str_custom - Only the str element of a
 * list_t linked list is printed.
 * @h: a reference to the first node
 *
 * Return: the list's number of nodes
 */
size_t print_list_str_custom(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * delete_node_at_index_custom - deletes the node at
 * the specified index
 * @index: node index to delete
 * @head: address of the initial node's pointer
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index_custom(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list -removes all nodes from a list
 * @head: a reference to the head node
 *
 * Return: void
 */
void free_list(list_t *head)
{
	list_t *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}


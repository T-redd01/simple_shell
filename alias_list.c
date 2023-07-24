#include "shel.h"

/**
 * print_al_list - print all nodes
 * @h: alias linked list
 */
void print_al_list(al_list *h)
{
	while (h)
	{
		_puts(h->name, 1);
		_puts("='", 1);
		_puts(h->val, 1);
		_puts("'\n", 1);
		h = h->n_al;
	}
}

/**
 * free_alias_list - free all nodes
 * @h: alias linked list
 */
void free_alias_list(al_list *h)
{
	al_list *curr, *next;
	
	curr = h;
	while (curr)
	{
		next = curr->n_al;
		free(curr->name);
		free(curr->val);
		free(curr);
		curr = next;
	}
}

/**
 * create_alias_node - creates a new alias node
 * @key: name of alias
 * @val: value of alias
 * Return: new node, null on fail
 */
al_list *create_alias_node(char *key, char *val)
{
	al_list *new = NULL;

	if (!key || !val)
		return (NULL);

	new = malloc(sizeof(al_list));
	if (!new)
	{
		perror("Error: failed to allocate memory");
		free(key);
		free(val);
		return (NULL);
	}

	new->name = key;
	new->val = val;
	new->n_al = NULL;

	return (new);
}

/**
 * prepend_al_node - add node to top of list
 * @h: address to pointer of start of list
 * @node: node to add
 */
void prepend_al_node(al_list **h, al_list *node)
{
	if (!node)
		return;

	node->n_al = *h;
	*h = node;
}


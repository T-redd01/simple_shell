#include "shel.h"

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

void prepend_al_node(al_list **h, al_list *node)
{
	if (!node)
		return;

	node->n_al = *h;
	*h = node;
}


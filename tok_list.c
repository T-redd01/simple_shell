#include "shel.h"

/**
 * create_tok_node - create token
 * @word: token
 * Return: new token node, null
 */
toks *create_tok_node(char *word)
{
	toks *new = NULL;

	new = malloc(sizeof(toks));
	if (!new)
	{
		perror("Error: create_tok_node");
		return (NULL);
	}

	new->token = word;
	new->n = NULL;
	return (new);
}

/**
 * append_tok_node - append node
 * @h: list
 * @node: node to append
 */
void append_tok_node(toks **h, toks *node)
{
	toks *tmp = *h;

	if (!node)
		return;

	if (!(*h))
	{
		*h = node;
		return;
	}

	while (tmp->n)
		tmp = tmp->n;
	tmp->n = node;
}

/**
 * print_toks_list - print tokens list
 * @h: start of list
 * Return: nodes, 0
 */
int print_toks_list(toks *h)
{
	int nodes = 0;

	if (!h)
		return (0);

	while (h)
	{
		nodes++;
		if (h->token)
			print_to_fd(1, h->token, NULL, NULL);
		else
			print_to_fd(1, "is nil", NULL, NULL);
		_putchar(1, '\n');
		h = h->n;
	}
	return (nodes);
}

/**
 * free_toks_list - free all nodes
 * @h: start of list
 */
void free_toks_list(toks **h)
{
	toks *tmp = NULL;

	if (!(*h))
		return;

	while (*h)
	{
		tmp = (*h)->n;
		if (((*h)->token))
			free(((*h)->token));
		free((*h));
		(*h) = tmp;
	}
	*h = NULL;
}


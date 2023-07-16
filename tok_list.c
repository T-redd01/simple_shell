#include "shel.h"

/* for tok list */
toks *create_toks_node(char *line, int pos, int len)
{
	int i;
	toks *new = NULL;

	if (!line)
		return (NULL);

	new = malloc(sizeof(toks));
	if (!new)
	{
		perror("Error: create_tok_node");
		return (NULL);
	}

	new->token = malloc((len + 1) * sizeof(char));
	if (!(new->token))
	{
		perror("Error: create_tok_node");
		free(new);
		return (NULL);
	}

	new->n = NULL;
	for (i = 0; (is_delim(line, pos)) == 0; i++, pos++)
		new->token[i] = line[pos];
	new->token[i] = '\0';
	return (new);
}


void append_toks_node(toks **h, toks *node)
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

int print_toks_list(toks *h)
{
	int nodes = 0;

	if (!h)
		return (0);

	while (h)
	{
		nodes++;
		print_to_fd(1, h->token, NULL, NULL);
		_putchar(1, '\n');
		h = h->n;
	}
	return (nodes);
}

void free_toks_list(toks **h)
{
	toks *tmp = NULL;

	if (!(*h))
		return;

	while (*h)
	{
		tmp = (*h)->n;
		free(((*h)->token));
		free((*h));
		(*h) = tmp;
	}
	*h = NULL;
}


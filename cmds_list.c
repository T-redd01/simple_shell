#include "shel.h"

cmds *create_cmd_node(toks *sub_h, char *line, int *i)
{
	cmds *node = NULL;

	if (!sub_h)
		return (NULL);

	node = malloc(sizeof(cmds));
	if (!node)
	{
		perror("Error: create_cmd_node");
		return (NULL);
	}
	node->token_l = sub_h;
	node->sym = 0;
	node->n = NULL;

	if (line[*i] == '\0' || line[*i] == '#')
		return (node);

	if (line[*i] == ';')
		node->sym = CMD_SEP;
	
	if (line[*i] == '&' && line[*i + 1] == '&')
	{
		node->sym = LOG_AND;
		*i += 1;
	}

	if (line[*i] == '|' && line[*i + 1] == '|')
	{
		node->sym = LOG_OR;
		*i += 1;
	}

	return (node);
}

void append_cmd_node(cmds **h, cmds *node)
{
	cmds *tmp;

	if (!node)
		return;

	if (!(*h))
	{
		*h = node;
		return;
	}

	tmp = *h;
	while (tmp->n)
		tmp = tmp->n;
	tmp->n = node;
}

int print_cmds_list(cmds *h)
{
	int nodes = 0;

	if (!h)
		return (0);

	while (h)
	{
		nodes++;
		print_to_fd(1, "command:\n", NULL, NULL);
		print_toks_list(h->token_l);
		printf("chainer: %d\n", h->sym);
		_putchar(1, '\n');
		h = h->n;
	}
	return (nodes);
}

void free_cmds_list(cmds **h)
{
	cmds *tmp;

	if (!(*h))
		return;

	tmp = *h;
	while (tmp)
	{
		tmp = (*h)->n;
		free_toks_list(&((*h)->token_l));
		free((*h));
		*h = tmp;
	}
	*h = NULL;
}


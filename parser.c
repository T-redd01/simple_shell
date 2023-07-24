#include "shel.h"

/**
 * is_delim - is character delimiter ?
 * @line: input given
 * @idx: current parser index
 * Return: 1 is a delimeter, 0 not a delimeter
 */
int is_delim(char *line, size_t idx)
{
	if (line[idx] == '\0')
		return (1);
	if (line[idx] == ' ')
		return (1);
	if (line[idx] == '\n')
		return (1);
	if (line[idx] == '#')
		return (1);
	if (line[idx] == ';')
		return (1);
	if (line[idx] == '&' && line[idx + 1] == '&')
		return (1);
	if (line[idx] == '|' && line[idx + 1] == '|')
		return (1);
	return (0);
}

/**
 * is_cmd_sep - is command delimeter ?
 * @line: input passed
 * @idx: index of parser
 * Return: 1 is delimeter, 0 not delimeter
 */
int is_cmd_sep(char *line, size_t *idx)
{
	if (!line)
		return (0);

	if (line[*idx] == '\0' || line[*idx] == '#')
		return (1);
	if (line[*idx + 1] == '\0')
		return (1);
	if (line[*idx] == ';')
		return (1);
	if (line[*idx] == '&' && line[*idx + 1] == '&')
	{
		*idx += 1;
		return (1);
	}
	if (line[*idx] == '|' && line[*idx + 1] == '|')
	{
		*idx += 1;
		return (1);
	}

	return (0);
}

/**
 * substitute_alias - check if command is alias
 * @h: alias list
 * @node: token with command
 */
void substitute_alias(al_list *h, toks *node)
{
	if (!h)
		return;

	while (h)
	{
		if ((my_strcmp(h->name, node->token)))
		{
			free(node->token);
			node->token = _strdup(h->val);
			return;
		}
		h = h->n_al;
	}
}

/**
 * create_cmd_vect - make vector of toks to evaluate
 * @m: program memory currently in use
 * @h: tokens
 * @count: number of tokens
 */
void create_cmd_vect(cache *m, toks *h, size_t count)
{
	size_t i = 0;
	char **vect = NULL;
	toks *tmp;

	if (!h)
		return;

	vect = malloc((count + 1) * sizeof(char *));
	if (!vect)
	{
		perror("Failed to allocate memory");
		free_toks_list(&h);
		return;
	}

	substitute_alias(m->als, h);
	while (h)
	{
		tmp = h->n;
		vect[i++] = h->token;
		free(h);
		h = tmp;
	}
	vect[i] = NULL;

	/* execute command */
	if ((_builtin(m, vect)))
		find_bin(m, vect);
	free_matrix(vect);
}

/**
 * parser - understand and evaluate input
 * @m: program memory in use
 * @line: input given
 */
void parser(cache *m, char *line)
{
	size_t i, args = 0;
	char *token = NULL;
	toks *node, *h = NULL;

	if (!line)
		return;

	for (i = 0; line[i]; i++)
	{
		if (!(is_delim(line, i)))
		{
			token = extract_word(m->env, line, &i);
			if (token)
			{
				node = create_tok_node(token);
				append_tok_node(&h, node);
				args++;
			}
		}

		if (is_cmd_sep(line, &i))
		{
			create_cmd_vect(m, h, args);
			/* if ran: should i chain next command */
			cmd_chaining(line, &i);
			h = NULL;
			args = 0;
		}

		if (line[i] == '#')
			break;

		if (line[i] == '\0')
			i--;
	}
	free_toks_list(&h);
}


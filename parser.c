#include "shel.h"

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

int is_cmd_sep(char *line, size_t *idx)
{
	if (!line)
		return (0);

	if (line[*idx] == '\0')
		return (1);
	if (line[*idx] == ';')
		return (1);
	if (line[*idx] == '&' && line[*idx + 1] == '&')
	{
		*idx += 1; /* increment for testing */
		return (1);
	}
	if (line[*idx] == '|' && line[*idx + 1] == '|')
	{
		*idx += 1; /* same here */
		return (1);
	}

	return (0);
}

char **create_cmd_vect(toks *h, size_t count)
{
	size_t i = 0;
	char **vect = NULL;
	toks *tmp;

	if (!h)
		return (NULL);

	vect = malloc((count + 1) * sizeof(char *));
	if (!vect)
	{
		perror("Failed to allocate memory");
		free_toks_list(&h);
		return (NULL);
	}

	while (h)
	{
		tmp = h->n;
		vect[i++] = h->token;
		free(h);
		h = tmp;
	}
	vect[i] = NULL;
	return (vect);
}


cmds *parser(char *line)
{
	size_t i, args = 0;
	char *token = NULL, **vect = NULL;
	toks *node, *h = NULL;

	if (!line)
		return (NULL);

	for (i = 0; line[i] && line[i] != '#'; i++)
	{
		
		if (!(is_delim(line, i)))
		{
			token = extract_word(line, &i);
			if (token)
			{
				node = create_tok_node(token);
				append_tok_node(&h, node);
				args++;
			}
		}

		if (is_cmd_sep(line, &i))
		{
			vect = create_cmd_vect(h, args);
			/* is command builtin / in path / non existant */
			/* if ran: should i chain next command */
			h = NULL;
			args = 0;
		}

		if (line[i] == '\0' || line[i] == '#')
			i--;
	}
	print_toks_list(h);
	free_toks_list(&h);
	return (NULL);
}


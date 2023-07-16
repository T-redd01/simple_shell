#include "shel.h"

size_t new_tok_len(char *word, char *ps, char *es, size_t *pl, size_t *el);

char *new_tok_str(size_t len, size_t p_str, size_t e_str, size_t p, size_t e)
{
	size_t i, j = 0;
	char *new_str = NULL, *val = NULL;

	new_str = malloc((len + 1) * sizeof(char));
	if (!new)
	{
		perror("Error: new_node");
		*flag = 0;
		return (node);
	}

	for (i = 0; node->token[i]; i++)
	{
		if (node->token[i] == '$' && node->token[i + 1] == '$')
		{
			new_str[j] = '\0';
			_strcat(new_str, p_str);
			j += p;
			i++;
		}
		else if (node->tokenp[i] == '$' && node->token[i +1] == '?')
		{
			new_str[j] = '\0';
			_strcat(new_str, e_str);
			j += e;
			i++;
		}
		else if (node->token[i] == '$' && node->token[i + 1] != '\0')
		{
			i++;
			val = get_env_val(node->token, &i);
			while (val && *val)
			{
				new_str[j++] = *val;
				val++;
			}
		}
		else
			new_str[j++] = node->token[i];
		
		if (node->token[i] == '\0')
				i--;
	}
	new_str[i] = '\0';
	return (new_str);
}


toks *new_node(toks *node, size_t *flag)
{
	size_t len = 0, p_len = 0, e_len = 0;
	char *new_str = NULL, *p_str = NULL, *e_str = NULL;
	toks *new_node = NULL;

	if (!node)
		return (NULL);

	p_len = getpid();
	p_str = _itoa(p_len);

	e_len = errno;
	e_str = _itoa(e_len);
	len = new_tok_len(node->token, p_str, e_str, &p_len, &e_len);
	if (len == 0)
	{
		*flag = 0;
		return (node);
	}

	new_str = new_tok_val(len, p_str, e_str, p_len, e_len);

	new_node = malloc(sizeof(toks));
	if (!new_node)
	{
		*flag = 0;
		perror("Error: new_node");
		return (node);
	}
	new_node->token = new_str;
	new_node->n = NULL;
	*flag = 1;
	return (new_node);
}

void exp_toks(toks **h)
{
	size_t len = 0, flag = 0;
	toks *head = NULL, *node = NULL, *tmp = NULL;

	if (!(*h))
		return;

	while (*h)
	{
		tmp = (*h)->n;
		node = new_node(tmp, &flag);
		if (node)
		{
			len++;
			append_toks_node(&h, node);
		}

		if (flag)
			free((*h));
		*h = tmp;
	}
	*h = head;

	m.cmd_vect = create_arg_vect(*h, len);
}

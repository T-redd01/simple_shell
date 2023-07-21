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

int is_cmd_sep(char *line, size_t idx)
{
	if (!line)
		return (0);

	if (line[idx] == '\0')
		return (1);
	if (line[idx] == ';')
		return (1);
	if (line[idx] == '&' && line[idx + 1] == '&')
		return (1);
	if (line[idx] == '|' && line[idx + 1] == '|')
		return (1);

	return (0);
}

char *make_tok_str(char *line, size_t *idx)
{
	size_t i = *idx, j = 0, len = 0;
	char *str = NULL;

	while (!(is_delim(line, *idx)))
	{
		len++; /* find len */
		*idx += 1;
	}

	str = malloc((len + 1) * sizeof(char));
	if (!str)
	{
		perror("Error: make_tok_str");
		return (NULL);
	}

	while (!(is_delim(line, i)))
		str[j++] = line[i++];
	str[j] = '\0';
	return (str);
}

cmds *parser(char *line)
{
	size_t i, args = 0;
	char *word = NULL;

	if (!line)
		return (NULL);

	for (i = 0; line[i]; i++)
	{
		
		if (!(is_delim(line, i)))
		{
			word = make_tok_str(line, &i);
			word = exp_str(word);
			node = create_tok_node(word);
			if (node)
				args++;
			append_tok_node(&h, node);
		}

		if (line[i] == '#')
			break;
		
		if (is_cmd_sep(line, i))
		{
			printf("seperator: %c\n\n", line[i]);
		}

		if (line[i] == '\0')
			i--;
	}
	return (NULL);
}


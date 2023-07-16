#include "shel.h"

int is_cmd_sep(char *line, int idx)
{
	if (!line)
		return (0);

	if (line[idx] == '\0' || line[idx] == '#')
		return (1);
	if (line[idx] == ';')
		return (1);
	if (line[idx] == '&' && line[idx + 1] == '&')
		return (1);
	if (line[idx] == '|' && line[idx + 1] == '|')
		return (1);

	return (0);
}

cmds *parser(char *line)
{
	int i, pos, len;
	toks *sub_h = NULL, *tok_node = NULL;
	cmds *h = NULL, *cmd_node = NULL;

	if (!line)
		return (NULL);

	for (i = 0; line[i]; i++)
	{
		if ((is_delim(line, i)) == 0)
		{
			pos = i;
			len = 0;
			while (line[i] && (is_delim(line, i)) == 0) {
				i++;
				len++;
			}
			tok_node = create_toks_node(line, pos, len);
			append_toks_node(&sub_h, tok_node);
		}

		if ((is_cmd_sep(line, i)))
		{
			cmd_node = create_cmd_node(sub_h, line, &i);
			append_cmd_node(&h, cmd_node);
			sub_h = NULL;
		}

		if (line[i] == '#')
			break;

		if (line[i] == '\0')
			i--;
	}
	return (h);
}


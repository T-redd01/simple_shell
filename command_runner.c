#include "shel.h"

int eval_loop(cache m)
{
	cmds *h = m.cmd_buff, *tmp = NULL;

	if (!h)
		return (1);

	while (h)
	{
		tmp = h->n;
		expand_toks(&(h->token_l));
		print_toks_list(h->token_l);
		free_toks_list(&(h->token_l));
		free(h);
		h = tmp;
	}
	return (0);
}

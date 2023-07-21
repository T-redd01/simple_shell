#include "shel.h"

char **cmd_vect(toks *h, int args)
{
	int i = 0;
	char **vect = NULL;
	toks *tmp = NULL;

	if (args == 0 || !h)
		return (NULL);

	vect = malloc((args + 1) * sizeof(char *));
	if (!vect)
	{
		perror("Error: cmd_vect");
		return (NULL);
	}

	while (h)
	{
		tmp = h->n;
		if (h->token)
			vect[i++] = h->token;
		h = tmp;
	}
	vect[i] = NULL;
	return (vect);
}

char **exp_toks(__attribute__((unused))toks *h)
{
	/*toks *tmp = NULL, *tmp2 = NULL;
	int args = 0, i = 0;
	char *str = NULL, **vect = NULL;

	tmp = h;
	while (tmp)
	{
		args++;
		tmp2 = tmp->n;
		str = exp_str(tmp->token, &i);
		if (i)
		{
			free(tmp->token);
			tmp->token = NULL;
		}
		tmp->token = str;
		if (!(tmp->token))
			args--;

		tmp = tmp2;
	}
	vect = cmd_vect(h, args);
	return (vect);*/
	return (NULL);
}

int eval_loop(cache m)
{
	/*int chain = 0;*/
	char **arg_vect = NULL;
	cmds *tmp = NULL;

	/*tmp = m.cmd_buff;*/
	while (m.cmd_buff)
	{
		tmp = (m.cmd_buff)->n;
		arg_vect = exp_toks((m.cmd_buff)->token_l);

		if ((find_builtin(m, arg_vect)))
			find_bin(m, arg_vect);

		free_toks_list(&((m.cmd_buff)->token_l));
		free(m.cmd_buff);
		m.cmd_buff = tmp;
		free(arg_vect);
		/*
		tmp = (m.cmd_buff)->n;
		arg_vect = exp_toks((m.cmd_buff)->token_l);
		chain = (m.cmd_buff)->sym;

		free_toks_list(&((m.cmd_buff)->token_l));
		free(m.cmd_buff);
		m.cmd_buff = tmp;

		if (arg_vect)
		{
			 check if builtin 
			 if not builtin check for bin 
		}
		 checking command chaining and skipping 
		while (m.cmd_buff && chain == LOG_AND && errno != 0)
		{
			tmp = (m.cmd_buff)->n;
			free_toks_list(&((m.cmd_buff)->token_l));
			free(m.cmd_buff);
			m.cmd_buff = tmp;
		}
		 figure out skipping one cmd for and 
		while (m.cmd_buff && chain == LOG_OR && errno == 0)
		{
			tmp = (m.cmd_buff)->n;
            free_toks_list(&((m.cmd_buff)->token_l));
            free(m.cmd_buff);
			m.cmd_buff = tmp;
		}
		 figure out skipping for or 
		 */
	}
	/*free_cmds_list(&tmp);*/
	return (0);
}

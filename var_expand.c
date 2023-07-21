#include "shel.h"

char *env_var_val(char *tok_str, size_t *idx)
{
	size_t len = 0, pos = *idx;
	char *var= NULL, *val = NULL;

	while (tok_str[*idx] && tok_str[*idx] != ' ')
	{
		len++;
		*idx += 1;
	}

	var = malloc((len + 1) * sizeof(char));
	if (!var)
	{
		perror("Error: env_var_val");
		return (NULL);
	}

	len = 0;
	while (tok_str[pos] && tok_str[pos] != ' ')
		var[len++] = tok_str[pos++];
	var[len] = '\0';

	val = _getenv(var);
	free(var);
	if (!val)
		return (NULL);
	return (val);
}

ssize_t get_new_len(char *old, size_t pl, size_t el)
{
	ssize_t len = 0;
	size_t i = 0, flag = 0;
	char *val = NULL;

	for (i = 0; old[i]; i++)
	{
		if (old[i] == '$' && old[i + 1] == '$')
		{
			flag = 1;
			len += pl;
			i++;
		}
		else if (old[i] == '$' && old[i + 1] == '?')
		{
			flag = 1;
			len += el;
			i++;
		}
		else if (old[i] == '$' && old[i + 1] != '\0')
		{
			flag = 1;
			i++;
			val = env_var_val(old, &i);
			len += (_strlen(val));
		}
		else
			len++;
		
		if (old[i] == '\0')
			i--;
	}

	if (flag == 0)
		return (0);

	if (len == 0)
		return (-1);
	return (len);
}

char *get_n_str(char *old, char *es, char *ps, size_t pl, size_t el, ssize_t l)
{
	size_t i, j = 0;
	char *n_str = NULL, *val = NULL;

	n_str = malloc((l + 1) * sizeof(char));
	if (!n_str)
		return (NULL);

	for (i = 0; old[i]; i++)
	{
		if (old[i] == '$' && old[i + 1] == '$')
		{
			n_str[j] = '\0';
			_strcat(n_str, ps);
			j += pl;
			i++;
		}
		else if (old[i] == '$' && old[i + 1] == '?')
		{
			n_str[j] = '\0';
			_strcat(n_str, es);
			j += el;
			i++;
		}
		else if (old[i] == '$' && old[i + 1] != '\0')
		{
			n_str[j] = '\0';
			i++;
			val = env_var_val(old, &i);
			_strcat(n_str, val);
			j += _strlen(val);
		}
		else
			n_str[j++] = old[i];

		if (old[i] == '\0')
			i--;
	}
	n_str[j] = '\0';
	return (n_str);
}

char *exp_str(char *old_str/*, int *flag*/)
{
	ssize_t len = 0;
	size_t pl = 0, el = 0;
	char *n_str = NULL, *ps = NULL, *es = NULL;

	pl = getpid();
	ps = _itoa(pl);
	pl = _strlen(ps);

	el = errno;
	es = _itoa(el);
	el = _strlen(es);

	len = get_new_len(old_str, pl, el);
	if (len == 0)
	{
		free(es);
		free(ps);
		/*flag = 0;*/
		return (old_str);
	}
	if (len == -1)
	{
		free(es);
		free(ps);
		free(old_str);
		return (NULL);
	}

	n_str = get_n_str(old_str, es, ps, pl, el, len);
	free(old_str);
	free(es);
	free(ps);
	return (n_str);
}


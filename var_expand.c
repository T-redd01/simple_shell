#include "shel.h"

char *get_env_val(char *line, size_t *idx)
{
	size_t pos, len = 0;
	char *key = NULL, *val = NULL;

	*idx += 1;
	pos = *idx;
	while (!(is_delim(line, *idx)))
	{
		len++;
		*idx += 1;
	}
	*idx -= 1;

	key = malloc((len + 1) * sizeof(char));
	if (!key)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}

	len = 0;
	while (!(is_delim(line, pos)))
		key[len++] = line[pos++];
	key[len] = '\0';

	val = _getenv(key);
	free(key);
	return (val);
}

size_t word_full_len(char *line, size_t idx, size_t pl, size_t el)
{
	size_t len = 0;

	for (; !(is_delim(line, idx)); idx++) {
		if (line[idx] == '$' && line[idx + 1] == '?')
		{
			idx++;
			len += el;
		}
		else if (line[idx] == '$' && line[idx + 1] == '$')
		{
			idx++;
			len += pl;
		}
		else if (line[idx] == '$' && !(is_delim(line, idx + 1)))
		{
			len += _strlen((get_env_val(line, &idx)));
		}
		else
			len++;

		if (line[idx] == '\0')
			idx--;
	}
	return (len);
}

char *exp_word(char *line, size_t *i, char * ps, size_t pl, char *es, size_t el, size_t l)
{
	size_t j = 0;
	char *token = NULL, *env_val;

	token = malloc((l + 1) * sizeof(char));
	if (!token)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}

	for (; !(is_delim(line, *i)); *i += 1)
	{
		if (line[*i] == '$' && line[*i + 1] == '$')
		{
			token[j] = '\0';
			_strcat(token, ps);
			j += pl;
			*i += 1;
		}
		else if (line[*i] == '$' && line[*i + 1] == '?')
		{
			token[j] = '\0';
			_strcat(token, es);
			j += el;
			*i += 1;
		}
		else if (line[*i] == '$' && !(is_delim(line, *i + 1)))
		{
			token[j] = '\0';
			env_val = get_env_val(line, i);
			_strcat(token, env_val);
			j += (_strlen(env_val));
		}
		else
			token[j++] = line[*i];

		if (line[*i] == '\0')
			*i -= 1;
	}
	token[j] = '\0';
	return (token);
}

char *extract_word(char *line, size_t *idx)
{
	size_t len, pl, el;
	char *str = NULL, *ps, *es;

	pl = getpid(); /* turn proc_id into string */
	ps = _itoa(pl);
	pl = _strlen(ps); /* save len of proc_id string */

	el = errno; /* turn errno into string */
	es = _itoa(errno);
	el = _strlen(es); /* save len of errno string */

	len = word_full_len(line, *idx, pl, el);
	if (len == 0)
	{
		while (!(is_delim(line, *idx)))
			*idx += 1;
		free(ps);
		free(es);
		return (NULL);
	}
	str = exp_word(line, idx, ps, pl, es, el, len);
	free(es);
	free(ps);
	return (str);
}


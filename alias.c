#include "shel.h"

/**
 * extract_al_key - extract key from key=val pair
 * @pair: pointer to full key=val string
 * Return: pointer to key
 */
char *extract_al_key(char *pair)
{
	size_t i = 0;
	char *key = NULL;

	if (*pair == '=')
		return (NULL);

	while (pair[i] && pair[i] != '=')
		i++;
	if (pair[i] != '=')
		return (NULL);

	key = malloc((i + 1) *sizeof(char));
	if (!key)
	{
		perror("Error: failed to allocate memory");
		return (NULL);
	}

	for (i = 0; pair[i] != '='; i++)
		key[i] = pair[i];
	key[i] = '\0';

	return (key);
}

/**
 * extract_al_val - extract value from key=val pair
 * @pair: pointer to key=val string
 * Return: pointer to val
 */
char *extract_al_val(char *pair)
{
	size_t i = 0;
	char *val = NULL;

	if (*pair == '=')
		return (NULL);

	while (pair[i] && pair[i] != '=')
		i++;
	if (pair[i] != '=')
		return (NULL);

	pair += (i + 1);

	val = malloc(((_strlen(pair)) + 1) * sizeof(char));
	if (!val)
	{
		perror("Error: failed to allocate memory");
		return (NULL);
	}

	for (i = 0; pair[i]; i++)
		val[i] = pair[i];
	val[i] = '\0';

	return (val);
}

/**
 * print_al_node - print key='val' from alias node
 * @node: struct with key and val
 */
void print_al_node(al_list *node)
{
	_puts(node->name, 1);
	_puts("='", 1);
	_puts(node->val, 1);
	_puts("'\n", 1);
}

/**
 * print_replace_alias - checks whether to print or replace node val
 * @h: alias linked list
 * @arg: string to compare
 * Return: 0 (Success), 1 (Failure)
 */
int print_replace_alias(al_list *h, __attribute__((unused))char *arg)
{
	size_t i;

	if (!h)
		return (1);

	while (h)
	{
		for (i = 0; h->name[i] && (arg[i] && arg[i] != '='); i++)
			if (h->name[i] != arg[i])
				break;

		if (h->name[i] == '\0' && arg[i] == '=')
		{
			free(h->val);
			h->val = extract_al_val(arg);
			return (0);
		}

		if (h->name[i] == arg[i])
		{
			print_al_node(h);
			return (0);
		}
		h = h->n_al;
	}
	return (1);
}

/**
 * _alias - builtin command alias
 * @m: memory that program is using
 * @vect: command being evaluated
 */
void _alias(__attribute__((unused))cache *m, __attribute__((unused))char **vect)
{
	int i;
	char *key, *val;
	al_list *node;

	if (!(vect[1]))
	{
		print_al_list(m->als);
		return;
	}

	for (i = 1; vect[i]; i++)
	{
		if ((print_replace_alias(m->als, vect[i])))
		{
			key = extract_al_key(vect[i]);
			val = extract_al_val(vect[i]);
			node = create_alias_node(key, val);
			prepend_al_node(&(m->als), node);
		}
	}
}


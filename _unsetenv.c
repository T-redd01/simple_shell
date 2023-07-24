#include "shel.h"

/**
 * _unsetenv - unset env var
 * @m: program memory in use
 * @name: var name
 * Return: 0 (Success), 1 (Failure)
 */
int _unsetenv(cache *m, char *name)
{
	int i, j, flag = 0;
	char **new = NULL;

	for (j = 0; (m->env)[j]; j++)
		if ((key_cmp((m->env)[j], name)))
		{
			flag = 1;
			continue;
		}

	if (flag == 0)
	{
		_puts("Variable not found\n", 2);
		return (1);
	}
	new = malloc(j * sizeof(char *));
	if (!new)
	{
		perror("Error: _unsetenv");
		return (1);
	}

	for (i = 0, j = 0; (m->env)[i]; i++)
	{
		if ((key_cmp((m->env)[i], name)))
		{
			free((m->env)[i]);
			continue;
		}
		new[j++] = (m->env)[i];
	}
	new[j] = NULL;
	free(m->env);
	m->env = new;
	return (0);
}

/**
 * call_unsetenv - check for errs
 * @m: program memory in use
 * @vect: command being evaluated
 */
void call_unsetenv(cache *m, char **vect)
{
	int i = 0;

	errno = 0;
	while (vect[i])
	{
		i++;
		if (i > 2)
		{
			_puts("Usage: unsetenv [VARIABLE_NAME]\n", 2);
			errno = 1;
			return;
		}
	}

	if (i < 2)
	{
		_puts("Usage: unsetenv [VARIABLE_NAME]\n", 2);
		errno = 1;
		return;
	}

	if ((_unsetenv(m, vect[1])))
		errno = 1;
}


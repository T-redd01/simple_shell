#include "shel.h"

/**
 * new_env_var - create new env var
 * @key: env var key
 * @val: env var val
 * Return: pointer to new env var
 */
char *new_env_var(char *key, char *val)
{
	int i, j = 0;
	char *var = NULL;

	var = malloc(((_strlen(key)) + (_strlen(val)) + 2) * sizeof(char));
	if (!var)
	{
		perror("Error: new_env_var");
		return (NULL);
	}

	for (i = 0; key[i]; i++)
		var[j++] = key[i];
	var[j++] = '=';

	for (i = 0; val[i]; i++)
		var[j++] = val[i];
	var[j] = '\0';
	return (var);
}

/**
 * _setenv - sets or replaces env var
 * @m: program memory in use
 * @name: name of env var
 * @value: value of var
 * Return: 0 (Success), 1 (Failure)
 */
int _setenv(cache *m, char *name, char *value)
{
	int i;
	char **new = NULL, *new_val = NULL;

	for (i = 0; (m->env)[i]; i++)
	{
		if ((key_cmp((m->env)[i], name)))
		{
			new_val = new_env_var(name, value);
			if (new_val)
			{
				free((m->env)[i]);
				(m->env)[i] = new_val;
				return (0);
			}
			return (1);
		}
	}

	new = malloc((i + 2) * sizeof(char *));
	if (!new)
	{
		perror("Error: _setenv");
		return (1);
	}

	for (i = 0; (m->env)[i]; i++)
		new[i] = (m->env)[i];
	new[i++] = new_env_var(name, value);
	new[i] = NULL;
	free(m->env);
	m->env = new;
	return (0);
}

/**
 * call_setenv - check command vect
 * @m: program memory in use
 * @vect: command being evaluated
 */
void call_setenv(cache *m, char **vect)
{
	int i = 0;

	errno = 0;
	while (vect[i])
	{
		i++;
		if (i > 3)
		{
			_puts("Usage: setenv [VARIABLE_NAME] [VARIABLE_VALUE]\n", 2);
			errno = 1;
			return;
		}
	}

	if (i < 3)
	{
		_puts("Usage: setenv [VARIABLE_NAME] [VARIABLE_VALUE]\n", 2);
		errno = 1;
		return;
	}

	if ((_setenv(m, vect[1], vect[2])))
		errno = 1;
}


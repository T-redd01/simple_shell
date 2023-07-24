#include "shel.h"

/**
 * print_env - prints all environment vars
 * @m: program memory in use
 * @vect: command being evaluated
 */
void print_env(cache *m, __attribute__((unused)) char **vect)
{
	errno = 0;
	print_matrix(m->env);
}

/**
 * _builtin - finds builtin cmd to run
 * @m: program memory in use
 * @vect: command being evaluated
 * Return: 0 command found, 1 command not found
 */
int _builtin(cache *m, char **vect)
{
	int i = 0;
	builtin_t arr[] = {
		{"exit", s_exit},
		{"alias", _alias},
		{"unsetenv", call_unsetenv},
		{"setenv", call_setenv},
		{"env", print_env},
		{"cd", change_WD},
		{NULL, NULL},
	};

	while (arr[i].builtin_name)
	{
		if ((my_strcmp(arr[i].builtin_name, vect[0])))
		{
			arr[i].fp(m, vect);
			return (0);
		}
		i++;
	}
	return (1);
}


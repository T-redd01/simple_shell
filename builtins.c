#include "shel.h"

void print_env(cache *m, __attribute__((unused)) char **vect)
{
	errno = 0;
	print_matrix(m->env);
}

int _builtin(__attribute__((unused))cache *m, __attribute__((unused))char **vect)
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
		if ((my_strcmp(arr[i].builtin_name, vect[0]))) {
			arr[i].fp(m, vect);
			return (0);
		}
		i++;
	}
	return (1);
}


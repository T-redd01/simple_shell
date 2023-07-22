#include "shel.h"

int _builtin(__attribute__((unused))cache m, __attribute__((unused))char **vect)
{
	int i = 0;
	builtin_t arr[] = {
		/*{"exit", _exit},*/
		{"alias", _alias},
		/*{"unsetenv", call_unsetenv},
		{"setenv", call_setenv},
		{"cd", change_WD},*/
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
	_putchar(1, '\n');
	return (1);
}


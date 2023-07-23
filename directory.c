#include "shel.h"

char *_getCWD(size_t num)
{
    char *buf = NULL;

    buf = malloc(num * sizeof(char));
    if (!buf) {
        perror("my_get: buf");
        return (NULL);
    }   

    getcwd(buf, num);
    if (errno == 34)
	{
        errno = 0;
        buf[0] = 'r';
        free(buf);
        return (_getCWD(num * 2));
    }   
    return (buf);
}

int go_HOME(cache *m, char *curr_dir)
{
	char *home = _getenv(m->env, "HOME");

	if (!home)
		return (1);

	if ((chdir(home)) == -1)
	{
		perror("Error: failed to change directory");
		return (1);
	}
	_setenv(m, "OLDPWD", curr_dir);
	_setenv(m, "PWD", home);

	return (0);
}

int go_PREV(cache *m, char *curr_dir)
{
	char *prev = _getenv(m->env, "OLDPWD");

	if (!prev)
	{
		_puts(curr_dir, 1);
		_putchar(1, '\n');
		return (1);
	}

	if ((chdir(prev)) == -1)
	{
		perror("Error: failed to change directory");
		return (1);
	}
	_puts(prev, 1);
	_putchar(1, '\n');
	_setenv(m, "PWD", prev);
	_setenv(m, "OLDPWD", curr_dir);

	return (0);
}

int go_DEST(cache *m, char *curr_dir, char *dest)
{
	if ((chdir(dest)) == -1)
	{
		print_to_fd(2, m->prmpt, "cd: ", "can't cd to ");
		_puts(dest, 2);
		_putchar(2, '\n');
		return (1);
	}
	_setenv(m, "OLDPWD", curr_dir);
	_setenv(m, "PWD", dest);

	return (0);
}

void change_WD(__attribute__((unused)) cache *m, __attribute__((unused)) char **vect)
{
	char *curr_dir = NULL;

	errno = 0;
	curr_dir = _getCWD(402);

	if (vect[1] == NULL)
	{
		go_HOME(m, curr_dir);
		free(curr_dir);
		return;
	}
	else if ((my_strcmp(vect[1], "-")))
	{
		go_PREV(m, curr_dir);
		free(curr_dir);
		return;
	}
	else
	{
		go_DEST(m, curr_dir, vect[1]);
		free(curr_dir);
		return;
	}
	free(curr_dir);
}

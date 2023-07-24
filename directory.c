#include "shel.h"

/**
 * _getCWD - recursively gets current directory path
 * @num: first size to allocate to buffer
 * Return: current directory path, NULL on fail
 */
char *_getCWD(size_t num)
{
	char *buf = NULL;

	buf = malloc(num * sizeof(char));
	if (!buf)
	{
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

/**
 * go_HOME - change to home directory
 * @m: program memory in use
 * @curr_dir: current working directory
 * Return: 0 (Success), 1 (Failure)
 */
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

/**
 * go_PREV - change to previous directory $OLDPWD
 * @m: program memory in use
 * @curr_dir: current working directory
 * Return: 0 (Succes), 1 (Failure)
 */
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

/**
 * go_DEST - change to given directory arg
 * @m: program memory in use
 * @curr_dir: current working directory
 * @dest: directory to change to
 * Return: 0 (Success), 1 (Failure)
 */
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

/**
 * change_WD - change directory (cd) builtin command
 * @m: program memory in use
 * @vect: command being evaluated
 */
void change_WD(cache *m, char **vect)
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


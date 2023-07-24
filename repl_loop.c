#include "shel.h"

/**
 * sighandler - func to handle SIGINT
 * @sig: signal received
 */
void sighandler(__attribute__((unused)) int sig)
{
	errno = 130;
	_putchar(1, '\n');
	_putchar(1, '$');
	_putchar(1, ' ');
}

/**
 * read_inp - read input into buffer
 * @input: where to store input
 * Return: num of chars read
 */
ssize_t read_inp(char **input)
{
	ssize_t rline;

	if (isatty(STDIN_FILENO))
	{
		_putchar(1, '$');
		_putchar(1, ' ');
	}
	rline = _getline(input, 0);
	return (rline);
}

/**
 * repl_loop - loop to capture and parse input
 * @m: program memory in use
 * @name: program name
 */
void repl_loop(cache *m, char *name)
{
	ssize_t g = 0;
	size_t runs = 0;

	signal(SIGINT, &sighandler);
	while (1)
	{
		runs++;
		g = read_inp(&(m->inp));
		if (g == -1)
		{
			if (isatty(STDIN_FILENO))
				_putchar(1, '\n');
			free_matrix(m->env);
			free_alias_list(m->als);
			exit(0);
		}

		if (g == 1 && *(m->inp) == '\n')
		{
			free(m->inp);
			continue;
		}
		m->prmpt = run_prmpt(runs, name);
		parser(m, m->inp);
		free(m->inp);
		free(m->prmpt);
	}
}


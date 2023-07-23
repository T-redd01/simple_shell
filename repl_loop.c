#include "shel.h"

void sighandler(__attribute__((unused)) int sig)
{
	errno = 130;
	_putchar(1, '\n');
	_putchar(1, '$');
	_putchar(1, ' ');
}

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

void repl_loop(__attribute__((unused)) cache *m, __attribute__((unused))char *name)
{
	ssize_t g = 0;
	size_t runs = 0;

	signal(SIGINT, &sighandler);
	while (1) {
		runs++;
		g = read_inp(&(m->inp));
		if (g == -1) {
			if (isatty(STDIN_FILENO))
				_putchar(1, '\n');
			free_matrix(m->env);
			free_alias_list(m->als);
			exit(0);
		}

		if (g == 1 && *(m->inp) == '\n') {
			free(m->inp);
			continue;
		}
		m->prmpt = run_prmpt(runs, name);
		parser(m, m->inp);
		free(m->inp);
		free(m->prmpt);
	}
}


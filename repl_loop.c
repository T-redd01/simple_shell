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

void repl_loop(__attribute__((unused)) cache m, char *name)
{
	ssize_t g = 0;
	size_t runs = 0;
	char *inp = NULL;

	signal(SIGINT, &sighandler);
	while (1) {
		runs++;
		g = read_inp(&inp);
		if (g == -1) {
			if (isatty(STDIN_FILENO))
				_putchar(1, '\n');
			free_matrix(m.env);
			exit(errno);
		}

		if (g == 1 && *inp == '\n') {
			free(inp);
			continue;
		}
		m.cmd_buff = parser(inp);
		free(inp);
		m.prmpt = run_prmpt(runs, name);
		eval_loop(m);
		free_cmds_list(&(m.cmd_buff));
	}
}


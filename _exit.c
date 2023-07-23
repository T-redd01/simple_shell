#include "shel.h"

void print_exit_err(char *prmpt, char *num) {
	if (!num)
		return;

	_puts(prmpt, 2);
	_puts("exit: Illegal number: ", 2);
	_puts(num, 2);
	_puts("\n", 2);
}

void s_exit(cache *m, char **vect) {
	int i, status = 0;

	if (!vect[1])
	{
		free_proc_mem(m, vect);
		exit(0);
	}

	for (i = 0; vect[1][i]; i++) {
		if (vect[1][i] < 48 || vect[1][i] > 57) {
			print_exit_err(m->prmpt, vect[1]);
			return;
		}
		status = (status * 10) + (vect[1][i] - 48);
	}
	free_proc_mem(m, vect);
	exit(status);
}

#include "shel.h"

int main(int ac, char **av) {
	/*int i = 0;*/
	cache m = {NULL, NULL, NULL};

	if (ac > 2) {
		print_to_fd(2, "Usage: ", av[0], " file_name\n");
		return (EXIT_FAILURE);
	}

	if (ac == 2) {
		print_to_fd(1, "file as arg: ", av[1], "\n");
	}

	m.env = init_env();
	repl_loop(m, av[0]);
	/*while (m.env[i]) {
		free(m.env[i]);
		i++;
	}
	free(m.env);*/
	return (0);
}


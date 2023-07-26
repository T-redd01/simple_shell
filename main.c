#include "shel.h"

/**
 * main - Entry point
 * @ac: num of CLI arg
 * @av: CLI args vector
 * Return: 0 (Success), 1 (Failure)
 */
int main(int ac, __attribute__((unused))char **av)
{
	cache m = {NULL, NULL, NULL, NULL};

	if (ac > 2)
	{
		print_to_fd(2, "Usage: ", av[0], " file_name\n");
		return (EXIT_FAILURE);
	}

	m.env = init_env();
	repl_loop(&m, av[0]);
	return (EXIT_SUCCESS);
}


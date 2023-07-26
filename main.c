#include "shel.h"

/**
 * main - Entry point
 * @ac: num of CLI arg
 * @av: CLI args vector
 * Return: 0 (Success), 1 (Failure)
 */
int main(int ac, __attribute__((unused))char **av)
{
	int fd;
	char *log = NULL;
	cache m = {NULL, NULL, NULL, NULL, NULL};

	if (ac > 2)
	{
		print_to_fd(2, "Usage: ", av[0], " file_name\n");
		return (EXIT_FAILURE);
	}

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			log = run_prmpt(0, av[0]);
			print_to_fd(2, log, "Can't open ", av[1]);
			_putchar(2, '\n');
			free(log);
			return (EXIT_FAILURE);
		}
		else
		{
			m.env = init_env();
			file_as_arg(fd, &m, av[1]);
			free_matrix(m.env);
			return (EXIT_SUCCESS);
		}
	}
	m.env = init_env();
	repl_loop(&m, av[0]);
	return (EXIT_SUCCESS);
}


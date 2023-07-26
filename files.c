#include "shel.h"

#define DEBUG 0

void file_as_arg(__attribute__((unused))int fd, __attribute__((unused))cache *m, __attribute__((unused))char *fname)
{
	ssize_t r;
	char *r_buff = NULL;

	r = _getline(&r_buff, fd);
	if (r == -1)
	{
		printf("returned -1\n");
		print_to_fd(2, "Error: failed to read from: ", fname, "\n");
		return;
	}
	else if (r == 0 || r == 1)
		return;

	/*evaluate_file_contents(m, fname, r_buff);*/
}

#if DEBUG

int main(int ac, char **av)
{
	int fd;
	cache m = {NULL, NULL, NULL, NULL};
	
	if (ac != 2)
	{
		printf("needs 1 file\n");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("couldnt open file\n");
		return (1);
	}

	file_as_arg(fd, &m, av[1]);
	return (0);
}

#endif

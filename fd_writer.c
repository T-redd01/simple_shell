#include "shel.h"

int load_buff(int fd, char *buff, char *s, size_t *idx) {
	size_t i = 0;
	int w;

	if (!s)
		return (1);

	while (s[i]) {
		if (*idx == 1024) {
			w = write(fd, buff, *idx);
			if (w == -1)
				return (1);
			*idx = 0;
		}
		buff[*idx] = s[i++];
		*idx += 1;
	}
	return (0);
}


int print_to_fd(int fd, char *s1, char *s2, char *s3) {
	size_t bytes = 0;
	int w;
	char buff[1024];

	if (s1)
		w = load_buff(fd, buff, s1, &bytes);

	if (s2 && w == 0)
		w = load_buff(fd, buff, s2, &bytes);

	if (s3 && w == 0)
		w = load_buff(fd, buff, s3, &bytes);

	if (bytes && w == 0) {
		w = write(fd, buff, bytes);
		if (w == -1)
			return (1);
	}
	return (0);
}

void _putchar(int fd, char c)
{
	write(fd, &c, 1);
}

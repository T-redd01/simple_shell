#include <stdio.h>

int main(__attribute__((unused)) int ac, char **av) {
	while (*av) {
		printf("%s\n", *av);
		av++;
	}
	return (0);
}

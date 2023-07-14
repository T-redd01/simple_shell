#include <stdio.h>

int main(void) {
	ssize_t g;
	size_t n = 0;
	char *line = NULL;

	printf("$ ");
	g = getline(&line, &n, stdin);
	if (g == -1) {
		printf("Error: got EOF\n");
		return (1);
	}
	printf("%s\n", line);
	free(line);

	return (0);
}

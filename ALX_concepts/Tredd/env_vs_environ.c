#include <stdio.h>

extern char **environ;

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **env) {
	printf("env: %p\n", (void *)env);
	printf("environ: %p\n", (void *)env);
	return (0);
}

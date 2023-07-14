#include "super_simple_shell.h"

void execute_cmd(char **cmd) {
	pid_t p;
	int status;

	p = fork();
	if (p == -1) {
		perror("Error: fork");
		return;
	}

	if (p == 0) {
		if (execve(cmd[0], cmd, environ) == -1) {
			perror("Error: execve");
			exit(98);
		}
	} else {
		wait(&status);
	}
}

int main(void) {
	ssize_t g;
	size_t n = 0;
	char *line = NULL, **args = NULL;

	while (1) {
		printf("$ ");
		g = getline(&line, &n, stdin);
		if (g == -1) {
			puts("\n...Closing shell");
			free(line);
			exit(0);
		}
		args = tokenate(line);
		if (args) {
			execute_cmd(args);
			free_matrix(args);
			args = NULL;
		}
		free(line);
		line = NULL;
	}
	return (0);
}

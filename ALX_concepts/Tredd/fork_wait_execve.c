#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void ls_5_times(char **cmd) {
	int i, status;
	pid_t f;

	for (i = 0; i < 5; i++) {
		f = fork();
		if (f == -1) {
			perror("Error: fork");
			return;
		}
		if (f == 0) {
			if (execve(cmd[0], cmd, environ) == -1) {
				perror("Error: execve");
				exit(98);
			}
		} else {
			wait(&status);
			printf("process execution finished\n\n");
		}
	}
}

int main(void) {
	char **cmd;

	cmd = malloc(4 * sizeof(char *));
	if (!cmd) {
		perror("Error: main");
		return (1);
	}
	cmd[0] = "/usr/bin/ls";
	cmd[1] = "-l";
	cmd[2] = "/tmp";
	cmd[3] = NULL;
	ls_5_times(cmd);
	free(cmd);
	return (0);
}

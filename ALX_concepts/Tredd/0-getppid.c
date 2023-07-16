#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	pid_t parent_pid;

	parent_pid = getppid();
	printf("%d\n", parent_pid);
	return (0);
}

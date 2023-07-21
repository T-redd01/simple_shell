#include "shel.h"

void free_proc_mem(cache m, char **vect)
{
	free(m.prmpt);
	free_matrix(m.env);
	free_cmds_list(&(m.cmd_buff));
	free(vect);
}

void cmd_executer(cache m, char *bin_name, char **vect)
{
	pid_t cp;
	int exec, status;

	cp = fork();
	if (cp == 0)
	{
		exec = execve(bin_name, vect, m.env);
		if (exec == -1)
		{
			perror("Error: execve failed");
			free_proc_mem(m, vect);
			kill((getpid()), SIGTERM);
		}
	}
	else
	{
		wait(&status);
		errno = WEXITSTATUS(status);
	}
}


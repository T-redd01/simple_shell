#include "shel.h"

/**
 * free_proc_mem - frees memory for program
 * @m: program memory in use
 * @vect: command being evaluated
 */
void free_proc_mem(cache *m, char **vect)
{
	free(m->prmpt);
	free_matrix(m->env);
	free(m->inp);
	free_alias_list(m->als);
	free_matrix(vect);
}

/**
 * exec_cmd - execute a command
 * @m: program memory in use
 * @bin_name: full_path to file/bin to execute
 * @vect: command being evaluated
 */
void exec_cmd(cache *m, char *bin_name, char **vect)
{
	pid_t cp;
	int exec, status;

	cp = fork();
	if (cp == 0)
	{
		exec = execve(bin_name, vect, m->env);
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


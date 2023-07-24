#include "shel.h"

/**
 * find_bin_err - print not found err
 * @prmpt: shell log
 * @name: cmd name
 */
void find_bin_err(char *prmpt, char *name)
{
	errno = 127;
	print_to_fd(2, prmpt, name, ": not found\n");
}

/**
 * create_bin_path - create path to passed cmd
 * @path: $PATH env var
 * @idx: index to start making path
 * @name: cmd name
 * Return: full path string, null
 */
char *create_bin_path(char *path, size_t *idx, char *name)
{
	size_t len = 0, pos = *idx;
	char *full_path = NULL;

	while (path[*idx] && path[*idx] != ':')
	{
		len++;
		*idx += 1;
	}

	full_path = malloc((len + (_strlen(name)) + 2) * sizeof(char));
	if (!full_path)
	{
		perror("Error: failed to allocate memory");
		return (NULL);
	}

	for (len = 0; path[pos] && path[pos] != ':'; pos++)
		full_path[len++] = path[pos];
	full_path[len] = '\0';

	_strcat(full_path, "/");
	_strcat(full_path, name);
	return (full_path);
}

/**
 * find_bin - find binary executable
 * @m: program memory in use
 * @vect: command being evaluated
 */
void find_bin(cache *m, char **vect)
{
	size_t i;
	char *path = _getenv(m->env, "PATH"), *fp;
	struct stat info;

	if ((stat(vect[0], &info)) == 0)
	{
		exec_cmd(m, vect[0], vect);
		return;
	}

	if (!path)
	{
		find_bin_err(m->prmpt, vect[0]);
		return;
	}

	for (i = 0; path[i]; i++)
	{
		if (path[i] && path[i] != ':')
		{
			fp = create_bin_path(path, &i, vect[0]);
			if ((stat(fp, &info)) == 0)
			{
				exec_cmd(m, fp, vect);
				free(fp);
				return;
			}
			free(fp);
		}

		if (path[i] == '\0')
			i--;
	}
	find_bin_err(m->prmpt, vect[0]);
}


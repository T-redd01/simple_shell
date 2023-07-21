#include "shel.h"

char *make_full_path(char *name, char *path, size_t *idx)
{
	size_t i = *idx, j = 0;
	char *f_p = NULL;

	if (!name || !path)
		return (NULL);

	while (path[*idx] && path[*idx] != ':')
	{
		j++;
		*idx += 1;
	}

	f_p = malloc((j + _strlen(name) + 2) * sizeof(char));
	if (!f_p)
	{
		perror("Error: make_full_path");
		return (NULL);
	}

	j = 0;
	while (path[i] && path[i] != ':')
		f_p[j++] = path[i++];
	f_p[j] = '\0';
	_strcat(f_p, "/");
	_strcat(f_p, name);
	return (f_p);
}

void not_found_err(char *prmpt, char *name)
{
	errno = 127;
	print_to_fd(2, prmpt, name, ": not found\n");
	return;
}

void find_bin(cache m, char **vect)
{
	size_t i;
	char *f_p = NULL, *path = _getenv("PATH");
	struct stat buf;

	if (!vect)
		return;

	if ((stat(vect[0], &buf)) == 0)
	{
		cmd_executer(m, vect[0], vect);
		return;
	}

	if (!path)
	{
		not_found_err(m.prmpt, vect[0]);
		return;
	}

	for (i = 0; path[i]; i++)
	{
		if (path[i] && path[i] != ':')
		{
			f_p = make_full_path(vect[0], path, &i);
			if ((stat(f_p, &buf)) == 0)
			{
				cmd_executer(m, f_p, vect);
				free(f_p);
				return;
			}
			free(f_p);
		}
	}
	not_found_err(m.prmpt, vect[0]);
}


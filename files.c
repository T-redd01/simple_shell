#include "shel.h"
/**
 * make_line - creates line from file buffer
 * @buff: contents of file
 * @idx: pointer to position of contents in file
 * Return: line from file
 */
char *make_line(char *buff, size_t *idx)
{
	size_t len = 0, pos = *idx;
	char *line = NULL;

	if (!buff)
		return (NULL);

	while (buff[*idx] && buff[*idx] != '\n' && buff[*idx] != 4)
	{
		len++;
		*idx += 1;
	}
	*idx -= 1;

	line = malloc((len + 1) * sizeof(char));
	if (!line)
	{
		perror("Error: failed to allocate memory");
		return (NULL);
	}

	for (len = 0; buff[pos] && buff[pos] != '\n' && buff[pos] != 4;)
		line[len++] = buff[pos++];
	line[len] = '\0';

	return (line);
}

/**
 * file_as_arg - if argument passed to shell opened successfully
 * @fd: file descriptor
 * @m: program memory in use
 * @fname: name of file / av[1]
 */
void file_as_arg(int fd, cache *m, char *fname)
{
	ssize_t r;
	size_t i = 0, runner = 0;

	r = _getline(&(m->fbuff), fd);
	if (r == -1)
	{
		print_to_fd(2, "Error: failed to read from: ", fname, "\n");
		return;
	}
	else if (r == 0 || r == 1)
		return;

	while (m->fbuff[i] && m->fbuff[i] != 4)
	{
		if (m->fbuff[i] && m->fbuff[i] != '\n' && m->fbuff[i] != 4)
		{
			runner++;
			m->inp = make_line(m->fbuff, &i);
			m->prmpt = run_prmpt(runner, fname);
			parser(m, m->inp);
			free(m->inp);
			free(m->prmpt);
		}
		i++;
	}
	free(m->fbuff);
}


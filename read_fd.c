#include "shel.h"

/**
 * _getline - reads everything from given fd
 * @buf: address of buffer to put into
 * @fd: file descriptor
 * Return: num of bytes read
 */
ssize_t _getline(char **buf, int fd)
{
	ssize_t r = 0, bytes = 0;
	int buffsize = 1023;
	char readbuf[1024];

	r = read(fd, readbuf, buffsize);
	if (r == 0)
		return (-1);

	*buf = malloc((r + 1) * sizeof(char));
	if (!(*buf))
	{
		perror("_getline: buf");
		return (0);
	}
	readbuf[r - 1] = '\0';
	_strcpy(*buf, readbuf);
	bytes += r;
	while (r == buffsize)
	{
		r = read(fd, readbuf, buffsize);
		readbuf[r - 1] = '\0';
		bytes += r;
		*buf = _realloc(*buf, (bytes + 1));
		if (!(*buf))
			return (0);

		_strcat(*buf, readbuf);
	}
	return (bytes);
}

/**
 * _realloc - reallocate a bigger buffer
 * @old: buffer
 * @new_size: new size to allocate
 * Return: pointer to new buffer
 */
char *_realloc(char *old, size_t new_size)
{
	char *new = NULL;

	new = malloc(new_size);
	if (!new)
	{
		perror("_realloc: new");
		return (NULL);
	}

	_strcpy(new, old);
	free(old);
	return (new);
}


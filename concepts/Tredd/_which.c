#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

int _strlen(char *s) {
	int len = 0;

	if (!s)
		return (0);

	while (s[len])
		len++;
	return (len);
}

void _strcat(char *dest, char *src) {
	int i = 0, j = 0;

	if (!src || !dest)
		return;

	while (dest[i])
		i++;

	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
}

int key_cmp(char *set_key, char *key) {
	int i;

	if (!set_key || !key)
		return (-1);

	for (i = 0; key[i] && (set_key[i] != '='); i++)
		if (key[i] != set_key[i])
			return (0);
	
	if (key[i] == '\0' && set_key[i] == '=')
		return (1);
	return (0);
}

char *_getenv(char *key) {
	int i;
	char *val = NULL;

	if (!key)
		return (NULL);

	for (i = 0; environ[i]; i++) {
		if ((key_cmp(environ[i], key))) {
			val = environ[i];
			while (*val != '=')
				val++;
			return (++val);
		}
	}
	return (NULL);
}

int path_tok_len(char *path, int idx) {
	int len = 0;

	if (!path)
		return (0);

	while (path[idx] && (path[idx] != ':')) {
		idx++;
		len++;
	}
	return (len);
}

int search_path(__attribute__((unused)) char *file) {
	int i, f_len = _strlen(file), p_len;
	char *path = NULL, *path_tok = NULL;
	struct stat info;

	if (!file)
		return (-1);

	if ((stat(file, &info)) == 0)
		return (1);

	path = _getenv("PATH");
	if (!path)
		return (-1);

	for (i = 0; path[i]; i++) {
		if (path[i] && path[i] != ':') {
			p_len = path_tok_len(path, i);
			path_tok = malloc((p_len + f_len + 2) * sizeof(char));
			if (!path) {
				perror("Error: search_path");
				return (-1);
			}
			p_len = 0;
			while (path[i] && (path[i] != ':'))
				path_tok[p_len++] = path[i++];
			path_tok[p_len] = '\0';
			_strcat(path_tok, "/");
			_strcat(path_tok, file);
			if ((stat(path_tok, &info)) == 0) {
				free(path_tok);
				return (1);
			}
			free(path_tok);
		}
	}
	return (0);
}

int main(int ac, char **av) {
	int i;

	if (ac < 2) {
		printf("Usage: %s file_name ...\n", av[0]);
		return (1);
	}

	for (i = 1; av[i]; i++) {
		if (search_path(av[i]))
			printf("%s: FILE FOUND IN PATH\n", av[i]);
		else
			printf("%s: FILE NOT FOUND IN PATH\n", av[i]);
	}
	return (0);
}

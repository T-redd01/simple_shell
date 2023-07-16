#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int key_cmp(char *set_key, const char *name) {
	int i;

	if (!set_key || !name)
		return (-1);

	for (i = 0; name[i] && (set_key[i] != '='); i++)
		if (name[i] != set_key[i])
			return (0);

	if (set_key[i] == '=' && name[i] == '\0')
		return (1);
	return (0);
}

int _strlen(char *s) {
	int len = 0;

	if (!s)
		return (0);

	while (s[len])
		len++;
	return (len);
}

char *_strdup(char *src) {
	int i = 0;
	char *new = NULL;

	if (!src)
		return (NULL);

	new = malloc((_strlen(src) + 1) * sizeof(char));
	if (!new) {
		perror("Error: _strdup");
		return (NULL);
	}

	while (src[i]) {
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void init_environ(void) {
	int i = 0;
	char **copy = NULL;

	while (environ[i])
		i++;

	copy = malloc((i + 1) * sizeof(char *));
	if (!copy) {
		perror("Error: init_environ");
		return;
	}

	for (i = 0; environ[i]; i++)
		copy[i] = _strdup(environ[i]);
	copy[i] = NULL;
	environ = copy;
}

int _unsetenv(const char *name) {
	int i, args, flag = 0;
	char **new = NULL;

	for (args = 0; environ[args]; args++) {
		if ((key_cmp(environ[args], name))) {
			flag = 1;
			continue;
		}
	}

	if (flag == 0) {
		printf("Var not found\n");
		return (1);
	}

	new = malloc((args) * sizeof(char *));
	if (!new) {
		perror("Error: _unsetenv");
		return (1);
	}

	args = 0;
	for (i = 0; environ[i]; i++) {
		if ((key_cmp(environ[i], name))) {
			free(environ[i]);
			continue;
		}
		new[args++] = environ[i];
	}
	new[args] = NULL;
	free(environ);
	environ = new;
	return (0);
}

int main(int ac, char **av) {
	int i = 0;

	if (ac != 2) {
		printf("Usage: %s <var_name>\n", av[0]);
		return (1);
	}
	init_environ();
	i = _unsetenv((const char *) av[1]);
	if (i)
		return (1);

	while (environ[i]) {
		printf("%s\n", environ[i]);
		free(environ[i]);
		i++;
	}
	free(environ);
	return (0);
}

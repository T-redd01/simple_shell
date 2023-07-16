#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/* strings */
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

/* env */
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

char *new_env_var(const char *key, const char *val) {
	int i, j = 0;
	char *var = NULL;

	if (!key || !val)
		return (NULL);

	var = malloc((_strlen((char *)key) + _strlen((char *)val) + 2) * sizeof(char));
	if (!var) {
		perror("Error: new_env_var:");
		return (NULL);
	}

	for (i = 0; key[i]; i++)
		var[j++] = key[i];
	var[j++] = '=';

	for (i = 0; val[i]; i++)
		var[j++] = val[i];
	var[j] = '\0';
	return (var);
}

int _setenv(const char *name, const char *value, int overwrite) {
	int i;
	char **new = NULL;

	if (!name || !value)
		return (1);

	for (i = 0; environ[i]; i++) {
		if ((key_cmp(environ[i], name))) {
			if (overwrite) {
				free(environ[i]);
				environ[i] = new_env_var(name, value);
				return (0);
			}
			return (1);
		}
	}

	new = malloc((i + 2) * sizeof(char *));
	if (!new) {
		perror("Error: _setenv");
		return (1);
	}

	for (i = 0; environ[i]; i++)
		new[i] = environ[i];
	new[i++] = new_env_var(name, value);
	new[i] = NULL;
	free(environ);
	environ = new;
	return (0);
}

int main(int ac, char **av) {
	int i;

	if (ac != 3) {
		printf("Usage: %s NAME VALUE\n", av[0]);
		return (1);
	}

	init_environ();
	i = _setenv(av[1], av[2], 1);
	while (environ[i]) {
		printf("%s\n", environ[i]);
		free(environ[i]);
		i++;
	}
	free(environ);
	return (0);
}


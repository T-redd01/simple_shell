#include <stdio.h>

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

char *_getenv(const char *name) {
	int i;
	char *val = NULL;

	if (!name)
		return (NULL);

	for (i = 0; environ[i]; i++) {
		if ((key_cmp(environ[i], name))) {
			val = environ[i];
			while (*val != '=')
				val++;
			return (++val);
		}
	}
	return (NULL);
}

int main(void) {
	int i;
	char *path = _getenv("PATH");

	for (i = 0; path[i]; i++) {
		if (path[i] && path[i] == ':') {
			puts("/");
			continue;
		}
		putchar(path[i]);
	}
	puts("/");
	return (0);
}

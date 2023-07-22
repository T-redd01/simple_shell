#include "shel.h"

char **init_env(void)
{
	int i = 0;
	char **copy = NULL;

	if (!environ)
		return (NULL);

	while (environ[i])
		i++;

	copy = malloc((i + 1) * sizeof(char *));
	if (!copy) {
		perror("Error: init_env");
		return (NULL);
	}

	for (i = 0; environ[i]; i++)
		copy[i] = _strdup(environ[i]);
	copy[i] = NULL;
	return (copy);
}

char *_getenv(char *name)
{
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


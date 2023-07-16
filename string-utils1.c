#include "shel.h"

size_t _strlen(char *s)
{
	size_t len = 0;

	if (!s)
		return (0);

	while (s[len])
		len++;
	return (len);
}


int _strcpy(char *dest, char *src) {
	size_t i, len = 0;

	if (src == NULL)
		return (1);

	len = _strlen(src);
	for (i = 0; i < len; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (0);
}

char *_strcat(char *dest, char *src) {
	size_t i, j;

	if (!src || !dest)
		return (NULL);

	for (i = 0; dest[i]; i++)
		;

	for (j = 0; src[j]; j++, i++)
		dest[i] = src[j];
	dest[i] = '\0';
	return (dest);
}

char *_strdup(char *src) {
	size_t i, len = 0;
	char *new = NULL;

	if (!src)
		return (NULL);

	while (src[len])
		len++;

	new = malloc((len + 1) * sizeof(char));
	if (!new) {
		perror("_strdup");
		return (NULL);
	}

	for (i = 0; src[i]; i++)
		new[i] = src[i];
	new[i] = '\0';
	return (new);
}

int my_strcmp(char *s1, char *s2) {
        size_t i;

        if (!s1 || !s2)
                return (0);

        for (i = 0; s1[i] && s2[i]; i++) {
                if (s1[i] != s2[i])
                        return (0);
        }
        if (s1[i] != s2[i])
                return (0);
        return (1);
}


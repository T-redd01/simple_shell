#include "shel.h"

char *extract_alias_name(char *pair) {
	int i, len = 0;
	char *key = NULL;

	if (!pair)
		return (NULL);

	while (pair[len] && pair[len] != '=')
		len++;

	if (pair[len] == '\0')
		return (NULL);

	key = malloc((len + 1) * sizeof(char));
	if (!key) {
		perror("extract_alias_name: key");
		return (NULL);
	}

	for (i = 0; pair[i] != '='; i++)
		key[i] = pair[i];
	key[i] = '\0';
	return (key);
}

char *extract_alias_val(char *pair) {
	int i, len = 0;
	char *val = NULL;

	if (!pair)
		return (NULL);

	while (*pair && *pair != '=')
		pair++;

	if (*pair == '\0')
		return (NULL);
	++pair;
	while (pair[len])
		len++;

	val = malloc((len + 1) * sizeof(char));
	if (!val) {
		perror("extract_alias_val: val");
		return (NULL);
	}
	for (i = 0; pair[i]; i++)
		val[i] = pair[i];
	val[i] = '\0';
	return (val);
}

al_list *change_alias_val(al_list *h, char *pair) {
	if (!h || !pair)
		return (NULL);

	while (h) {
		if ((key_cmp(pair, h->name))) {
			free(h->val);
			h->val = extract_alias_val(pair);
			return (h);
		}
		h = h->n_al;
	}
	return (NULL);
}

void _alias(cache m, char **vect) {
	int i, j;
	al_list *new = NULL;

	errno = 0;
	if (!vect)
		return;

	if (!vect[1]) {
		print_alias_list(m.als);
		return;
	}

	for (i = 1; vect[i]; i++) {
		for (j = 0; vect[i][j]; j++) {
			if (vect[i][j] == '=') {
				if ((change_alias_val(m.als, vect[i])))
					break;
				new = creat_alias_node(vect[i]);
				prepend_alias_node(&(m.als), new);
				print_alias_list(m.als);
				break;
			}
		}
		if (vect[i][j] != '=')
			print_alias_node(m.als, vect[i]);
	}
}


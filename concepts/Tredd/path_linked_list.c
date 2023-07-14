#include <stdio.h>
#include <stdlib.h>

typedef struct paths {
	char *sub_path;
	struct paths *next;
} path_list;

extern char **environ;

/* for path env */

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

/* end */

int path_tok_len(char *path, int idx) {
	int len = 0;

	if (!path)
		return (-1);
	
	while (path[idx] && path[idx] != ':') {
		idx++;
		len++;
	}
	return (len);
}

path_list *append_path_node(path_list **h, char *tok) {
	path_list *tmp = *h, *new = NULL;

	if (!tok)
		return (NULL);

	new = malloc(sizeof(path_list));
	if (!new) {
		perror("Error: append_path_node");
		free(tok);
		return (NULL);
	}
	new->sub_path = tok;
	new->next = NULL;

	if (!(*h)) {
		*h = new;
		return (new);
	}

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}

void print_path_list(path_list *h) {
	if (!h)
		return;

	while (h) {
		printf("%s\n", h->sub_path);
		h = h->next;
	}
}

void free_path_list(path_list *h) {
	path_list *tmp;

	if (!h)
		return;

	while (h) {
		tmp = h->next;
		free(h->sub_path);
		free(h);
		h = tmp;
	}
}

path_list *create_path_list(void) {
	int i, p_len;
	char *path_tok = NULL, *path;
	path_list *head = NULL/*, *node = NULL*/;

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	for (i = 0; path[i]; i++) {
		if (path[i] && path[i] != ':') {
			p_len = path_tok_len(path, i);
			path_tok = malloc((p_len + 2) * sizeof(char));
			if (!path) {
				perror("Error: create_path_list");
				free_path_list(head);
				return (NULL);
			}
			p_len = 0;
			while (path[i] && path[i] != ':')
				path_tok[p_len++] = path[i++];
			path_tok[p_len++] = '/';
			path_tok[p_len] = '\0';
			append_path_node(&head, path_tok);
		}
		if (path[i] == '\0')
			i--;
	}
	return (head);
}

int main(void) {
	path_list *h = NULL;

	h = create_path_list();
	print_path_list(h);
	free_path_list(h);
	return (0);
}


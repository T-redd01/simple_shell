#include "shel.h"

al_list *creat_alias_node(char *key_val) {
	al_list *new = NULL;

	if (!key_val) {
		return (NULL);
	}

	new = malloc(sizeof(al_list));
	if (!new) {
		perror("create_alias_node: new");
		return (NULL);
	}

	new->name = extract_alias_name(key_val);
	if (!new->name) {
		free(new);
		return (NULL);
	}
	new->val = extract_alias_val(key_val);
	if (!new->val) {
		free(new->name);
		free(new);
		return (NULL);
	}
	new->n_al = NULL;
	return (new);
}

void prepend_alias_node(al_list **h, al_list *node) {
	al_list *tmp = NULL;

	if (!node)
		return;

	if (!(*h)) {
		*h = node;
		return;
	}

	tmp = *h;
	*h = node;
	node->n_al = tmp;
}

void print_alias_node(al_list *h, char *key) {
	if (!h || !key)
		return;

	while (h) {
		if ((my_strcmp(h->name, key))) {
			_puts(h->name, 1);
			_puts("=", 1);
			_puts("'", 1);
			_puts(h->val, 1);
			_puts("'\n", 1);
			return;
		}
		h = h->n_al;
	}
}

void print_alias_list(al_list *h) {
	if (!h)
		return;

	while (h) {
		_puts(h->name, 1);
		_puts("=", 1);
		_puts("'", 1);
		_puts(h->val, 1);
		_puts("'\n", 1);
		h = h->n_al;
	}
}

void free_alias_list(al_list *h) {
	al_list *tmp = NULL;

	if (!h)
		return;

	while (h) {
		tmp = h->n_al;
		free(h->name);
		free(h->val);
		free(h);
		h = tmp;
	}
}


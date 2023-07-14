#include "super_simple_shell.h"

void free_matrix(char **matrix) {
	int i;

	if (!matrix || !(*matrix))
		return;

	for (i = 0; matrix[i]; i++)
		free(matrix[i]);
	free(matrix);
}

int find_delim(char *line) {
	if (*line == ' ')
		return (1);
	if (*line == '\n')
		return (1);
	return (0);
}

char *extract_word(char *line, int *pos) {
	int i = *pos, len = 0;
	char *word = NULL;

	if (!line)
		return (NULL);

	while (line[i] && !(find_delim(line + i))) {
		i++;
		len++;
	}

	word = malloc((len + 1) * sizeof(char));
	if (!word) {
		perror("Error: extract_word");
		return (NULL);
	}

	i = 0;
	while (line[*pos] && !(find_delim(line + (*pos)))) {
		word[i++] = line[*pos];
		*pos += 1;
	}
	word[i] = '\0';
	return (word);
}

char **tokenate(char *line) {
	int i, j = 0, len = 0;
	char **toks = NULL;

	for (i = 0; line[i]; i++) {
		if (line[i] && !(find_delim(line + i))) {
			len++;
			while (line[i] && !(find_delim(line + i)))
				i++;
		}

		if (line[i] == '\0')
			i--;
	}

	toks = malloc((len + 1) * sizeof(char *));
	if (!toks) {
		perror("Error: tokenate");
		return (NULL);
	}

	for (i = 0; line[i]; i++) {
		if (line[i] && !(find_delim(line + i)))
			toks[j++] = extract_word(line, &i);
		if (line[i] == '\0')
			i--;
	}
	toks[j] = NULL;
	return (toks);
}

/*
int main(void) {
	ssize_t g;
	size_t n = 0, i = 0;
	char *line = NULL, **args = NULL;

	puts("$ ");
	g = getline(&line, &n, stdin);
	if (g == -1) {
		printf("Error: got EOF\n");
		return (1);
	}
	args = tokenate(line);

	while (args[i]) {
		printf("%s\n", args[i]);
		i++;
	}
	return (0);
}
*/

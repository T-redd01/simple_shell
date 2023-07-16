#include "shel.h"

void free_matrix(char **matrix)
{
	int i;

	if (!matrix)
		return;

	for (i = 0; matrix[i]; i++)
		free(matrix[i]);
	free(matrix);
}

int is_delim(char *line, int idx)
{
	if (line[idx] == '\0')
		return (1);
	if (line[idx] == ' ')
		return (1);
	if (line[idx] == '\n')
		return (1);
	if (line[idx] == '#')
		return (1);
	if (line[idx] == ';')
		return (1);
	if (line[idx] == '&' && line[idx + 1] == '&')
		return (1);
	if (line[idx] == '|' && line[idx + 1] == '|')
		return (1);
	
	return (0);
}

char *run_prmpt(size_t runs, char *name)
{
	char *prmpt = NULL, *num = _itoa(runs);

	if (!name)
		return (NULL);

	prmpt = malloc((_strlen(name) + _strlen(num) + 5) * sizeof(char));
	if (!prmpt)
	{
		perror("Error: run_prmpt");
		return (NULL);
	}

	_strcpy(prmpt, name);
	_strcat(prmpt, ": ");
	_strcat(prmpt, num);
	free(num);
	_strcat(prmpt, ": ");
	return (prmpt);
}


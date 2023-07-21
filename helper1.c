#include "shel.h"

void print_matrix(char **matrix)
{
	int i;

	if (!matrix)
		return;

	for (i = 0; matrix[i]; i++)
	{
		print_to_fd(1, matrix[i], NULL, NULL);
		_putchar(1, '\n');
	}
}

void free_matrix(char **matrix)
{
	int i;

	if (!matrix)
		return;

	for (i = 0; matrix[i]; i++)
		free(matrix[i]);
	free(matrix);
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


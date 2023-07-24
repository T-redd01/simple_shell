#include "shel.h"

/**
 * print_matrix - prints a matrix of strings
 * @matrix: vector with strings
 */
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

/**
 * free_matrix - free a matrix of strings
 * @matrix: vector with strings
 */
void free_matrix(char **matrix)
{
	int i;

	if (!matrix)
		return;

	for (i = 0; matrix[i]; i++)
		free(matrix[i]);
	free(matrix);
}

/**
 * run_prmpt: creates log of shell
 * @runs: times repl loop ran
 * @name: program name
 * Return: pointer to log string, null
 */
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


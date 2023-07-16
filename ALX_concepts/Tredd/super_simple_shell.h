#ifndef SUPER_SIMPLE_SHELL_H
#define SUPER_SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* tokenator.c */
char **tokenate(char *line);
char *extract_word(char *line, int *pos);
int find_delim(char *line);
void free_matrix(char **matrix);

/* super_simple_shell */
void execute_cmd(char **cmd);

#endif

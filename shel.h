#ifndef SHEL_H
#define SHEL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define LOG_AND 1
#define LOG_OR 2
#define CMD_SEP 3

extern char **environ;

typedef struct token_list
{
	char *token;
	struct token_list *n;
} toks;

typedef struct alias_list {
	char *name;
	char *val;
	struct alias_list *n_al;
} al_list;

typedef struct shell_cache
{
	char **env;
	char *inp;
	char *prmpt;
	al_list *als;
} cache;

typedef struct builtins_s
{
	char *builtin_name;
	void (*fp) (cache m, char **vect);
} builtin_t;

/****************************************** CORE ******************************************/
/* repl_loop.c */
void repl_loop(cache m, char *name);
ssize_t read_inp(char **input);
void sighandler(int sig);

/* parser.c */
void parser(cache m, char *line);
int is_cmd_sep(char *line, size_t *idx);
int is_delim(char *line, size_t idx);

/* var_expand.c */
char *get_env_val(char *line, size_t *idx);
size_t word_full_len(char *line, size_t idx, size_t pl, size_t el);
char *exp_word(char *line, size_t *i, char * ps, size_t pl, char *es, size_t el, size_t l);
char *extract_word(char *line, size_t *idx);

/* builtins.c */
int _builtin(cache m, char **vect);

/* find_binary.c */
void find_bin(cache m, char **vect);

/* execute_cmd.c */
void exec_cmd(cache m, char *bin_name, char **vect);

/* tok_list.c */
toks *create_tok_node(char *word);
void append_tok_node(toks **h, toks *node);
int print_toks_list(toks *h);
void free_toks_list(toks **h);

/* _alias.c */
void _alias(cache m, char **vect);
al_list *change_alias_val(al_list *h, char *pair);
char *extract_alias_val(char *pair);
char *extract_alias_name(char *pair);

/* alias_linked_list.c */
al_list *creat_alias_node(char *key_val);
void prepend_alias_node(al_list **h, al_list *node);
void print_alias_node(al_list *h, char *key);
void print_alias_list(al_list *h);
void free_alias_list(al_list *h);

/************************************* UTILITIES ***************************************/
/* shell_environment.c */
char **init_env(void);
char *_getenv(char *name);

/* fd_writer.c */
int print_to_fd(int fd, char *s1, char *s2, char *s3);
int load_buff(int fd, char *buff, char *s, size_t *idx);
void _putchar(int fd, char c);
void _puts(char *s, int fd);

/* read_fd */
char *_realloc(char *old, size_t new_size);
ssize_t _getline(char **buf, int fd);

/* string-utils1.c */
size_t _strlen(char *s);
char *_strdup(char *src);
char *_strcat(char *dest, char *src);
int _strcpy(char *dest, char *src);
int my_strcmp(char *s1, char *s2);

/* string-utils2.c */
char *_itoa(size_t num);
int key_cmp(char *set_key, char *name);

/* helper1.c */
void print_matrix(char **matrix);
void free_matrix(char **matrix);
char *run_prmpt(size_t runs, char *name);

#endif


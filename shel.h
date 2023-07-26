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

/**
 * struct token_list - list of tokens before delims
 * @token: extracted token without delims
 * @n: next node in list
 *
 * Description: holds tokens that need to be turned into cmd vect
 */
typedef struct token_list
{
	char *token;
	struct token_list *n;
} toks;

/**
 * struct alias_list - holds memory to be passed between funcs
 * @name: alias name
 * @val: alias value
 * @n_al: alias list in use
 *
 * Description: holds memory and variables that funcs and program uses
 */
typedef struct alias_list
{
	char *name;
	char *val;
	struct alias_list *n_al;
} al_list;

/**
 * struct shell_cache - holds memory to be passed between funcs
 * @env: vect of environment vars on heap
 * @inp: input from user
 * @prmpt: shell log with name
 * @als: alias list in use
 *
 * Description: holds memory and variables that funcs and program uses
 */
typedef struct shell_cache
{
	char **env;
	char *inp;
	char *prmpt;
	al_list *als;
} cache;

/**
 * struct builtins_s - builtin functions
 * @builtin_name: name of builtin command
 * @fp: function pointer
 *
 * Description: all builtin commands for shell
 */
typedef struct builtins_s
{
	char *builtin_name;
	void (*fp)(cache *m, char **vect);
} builtin_t;

/****************************************** CORE *****************************/
/* repl_loop.c */
void repl_loop(cache *m, char *name);
ssize_t read_inp(char **input);
void sighandler(int sig);

/* parser.c */
void parser(cache *m, char *line);
int is_cmd_sep(char *line, size_t *idx);
int is_delim(char *line, size_t idx);

/* var_expand.c */
char *get_env_val(char **env, char *line, size_t *idx);
size_t word_full_len(char **env, char *line, size_t idx, size_t pl, size_t el);
char *exp_word(char **env, char *line, size_t *i, char *ps,
		size_t pl, char *es, size_t el, size_t l);
char *extract_word(char **env, char *line, size_t *idx);

/* builtins.c */
int _builtin(cache *m, char **vect);
void print_env(cache *m, char **vect);

/* find_binary.c */
void find_bin(cache *m, char **vect);

/* execute_cmd.c */
void exec_cmd(cache *m, char *bin_name, char **vect);
void free_proc_mem(cache *m, char **vect);

/* files.c */
void file_as_arg(int fd, cache *m, char *fname);

/* tok_list.c */
toks *create_tok_node(char *word);
void append_tok_node(toks **h, toks *node);
int print_toks_list(toks *h);
void free_toks_list(toks **h);

/************************************* BUILTINS *****************************/
/* alias.c */
void _alias(cache *m, char **vect);
int print_replace_alias(al_list *h, char *arg);
void print_al_node(al_list *node);
char *extract_al_val(char *pair);
char *extract_al_key(char *pair);

/* alias_list.c */
void print_al_list(al_list *h);
void free_alias_list(al_list *h);
al_list *create_alias_node(char *key, char *val);
void prepend_al_node(al_list **h, al_list *node);

/* _exit.c */
void s_exit(cache *m, char **vect);

/* _setenv.c */
char *new_env_var(char *key, char *val);
int _setenv(cache *m, char *name, char *value);
void call_setenv(cache *m, char **vect);

/* _unsetenv.c */
void call_unsetenv(cache *m, char **vect);
int _unsetenv(cache *m, char *name);

/* directory.c */
char *getCWD(size_t num);
void change_WD(cache *m, char **vect);

/************************************* UTILITIES ****************************/
/* shell_environment.c */
char **init_env(void);
char *_getenv(char **env, char *name);

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
void cmd_chaining(char *line, size_t *idx);

#endif


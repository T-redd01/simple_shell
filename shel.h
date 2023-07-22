#ifndef SHEL_H
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

typedef struct cmd_tok_list
{
	toks *token_l;
	int sym;
	struct cmd_tok_list *n;
} cmds;

typedef struct shell_cache
{
	char **env;
	char *full_cmd;
	char *inp;
	cmds *cmd_buff;
	char *prmpt;
} cache;

/****************************************** CORE ******************************************/
/* repl_loop.c */
void repl_loop(cache m, char *name);
ssize_t read_inp(char **input);
void sighandler(int sig);

/* parser.c */
cmds *parser(char *line);
int is_cmd_sep(char *line, size_t *idx);

/* command_runner.c */
char **cmd_vect(toks *h, int args);
int eval_loop(cache m);
char **exp_toks(toks *h);

/* var_expand.c */
char *get_env_val(char *line, size_t *idx);
size_t word_full_len(char *line, size_t idx, size_t pl, size_t el);
char *exp_word(char *line, size_t *i, char * ps, size_t pl, char *es, size_t el, size_t l);
char *extract_word(char *line, size_t *idx);

/* builtins.c */
int find_builtin(cache m, char **vect);

/* find_binary.c */
void find_bin(cache m, char **vect);

/* execute_cmd.c */
void cmd_executer(cache m, char *bin_name, char **vect);

/* tok_list.c */
toks *create_tok_node(char *word);
void append_tok_node(toks **h, toks *node);
int print_toks_list(toks *h);
void free_toks_list(toks **h);

/* cmds_list.c */
cmds *create_cmd_node(toks *sub_h, char *line, int *i);
void append_cmd_node(cmds **h, cmds *node);
int print_cmds_list(cmds *h);
void free_cmds_list(cmds **h);

/************************************* UTILITIES ***************************************/
/* shell_environment.c */
char **init_env(void);
char *_getenv(char *name);

/* fd_writer.c */
int print_to_fd(int fd, char *s1, char *s2, char *s3);
int load_buff(int fd, char *buff, char *s, size_t *idx);
void _putchar(int fd, char c);

/* read_fd */
char *_realloc(char *old, size_t new_size);
ssize_t _getline(char **buf, int fd);

/* string-utils1.c */
size_t _strlen(char *s);
char *_strdup(char *src);
char *_strcat(char *dest, char *src);
int _strcpy(char *dest, char *src);

/* string-utils2.c */
char *_itoa(size_t num);
int key_cmp(char *set_key, char *name);

/* helper1.c */
void print_matrix(char **matrix);
void free_matrix(char **matrix);
void print_matrix(char **matrix);
int is_delim(char *line, size_t idx);
char *run_prmpt(size_t runs, char *name);


#endif


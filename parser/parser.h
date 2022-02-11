#ifndef PARSER_H
#define PARSER_H
#include "libft.h"
#include <stdbool.h>
#include "lexer.h"
typedef struct s_cmd {
	int type;
} t_cmd;
typedef struct s_redirect_cmd
{
	int type;
	t_cmd *cmd;
	t_list *filenames_in;
	t_list *filenames_out;

} t_redirect_cmd;

typedef struct s_exec_cmd
{
	int type;
	char *cmd;
	t_list *args;
} t_exec_cmd;

typedef struct s_file
{
	char *filename;
	bool is_append;
} t_file;

typedef enum e_cmd_type {
	CMD_REDIRECT,
	CMD_PIPE,
	CMD_EXEC,
} t_cmd_type;

t_list *parse_pipe(t_list *token_list);
t_cmd *parse_exec(t_list *token_list);
t_cmd *parse_redirect(t_list *token_list);
void print_cmd(t_list *cmd);
void delete_cmd(t_cmd **cmd);
t_file *new_file(t_token *token, bool is_append);
void delete_file(void *file_ptr);
void delete_pipe(void *cmd);

#endif

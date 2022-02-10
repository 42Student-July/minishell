#ifndef LEXER_H
# define LEXER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

typedef enum e_tokentype
{
	TOKEN_ILLEGAL = -1,
	TOKEN_EOF = 0,
	TOKEN_IDENT = 1,
	TOKEN_NUMBER = 2,
	TOKEN_STRING,
	TOKEN_ASSIGN = '=',
	TOKEN_SQUOTE = '\'',
	TOKEN_DQUOTE = '"',
	TOKEN_REDIRECT_IN = '<',
	TOKEN_REDIRECT_OUT = '>',
	TOKEN_PIPE = '|',
	TOKEN_ENV = '$',
	TOKEN_WHITESPACE = ' ',
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EXIT_STATUS,
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*literal;
}	t_token;

typedef struct s_lexer
{
	char		*input;
	size_t		position;
	size_t		read_position;
	char		ch;
}	t_lexer;

t_lexer *new_lexer(char *input);
void delete_lexer(t_lexer *lexer);
void	read_char(t_lexer *lexer);
t_token *new_token(t_tokentype type, char *literal);
t_token *next_token(t_lexer *lexer);
void delete_token(void *token);
void print_token(t_token *token);
t_token *new_ident_token(t_lexer *lexer);
t_token *new_env_token(t_lexer *lexer);
char peek_char(t_lexer *lexer);
void print_tokens(t_list *token_list);
char *get_literal(t_token *token);
bool is_redirect(t_tokentype type);
void skip_whitespace(t_lexer *lexer);

#endif

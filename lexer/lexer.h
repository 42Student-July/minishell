#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
typedef enum e_tokentype
{
	TOKEN_ILLEGAL = -1,
	TOKEN_EOF = 0,
	TOKEN_IDENT = 1,
	TOKEN_REDIRECT_IN = '<',
	TOKEN_REDIRECT_OUT = '>',
	TOKEN_PIPE = '|',
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
}				t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*literal;
}				t_token;

typedef struct s_lexer
{
	char		*input;
	size_t		position;
	size_t		read_position;
	char		ch;
	bool		skip_whitespace;
	t_list		*io_here_delimiters;
	t_list		*heredocs;
}				t_lexer;

typedef struct s_lexer_product
{
	t_list		*token_list;
	t_list		*heredocs;
}				t_lexer_product;

t_lexer			*new_lexer(const char *input);
void			delete_lexer(t_lexer *lexer);
void			delete_lexer_without_heredocs(t_lexer *lexer);
void			delete_lexer_product(t_lexer_product *lexer_product);
void			read_char(t_lexer *lexer);
t_token			*new_token(t_tokentype type, char *literal);
t_token			*next_token(t_lexer *lexer);
void			delete_token(void *token);
void			print_token(t_token *token);
t_token			*new_ident_token(t_lexer *lexer);
t_token			*new_env_token(t_lexer *lexer);
char			peek_char(t_lexer *lexer);
void			print_tokens(t_list *token_list);
char			*get_literal(t_token *token);
bool			is_redirect(t_tokentype type);
void			skip_whitespace(t_lexer *lexer);
bool			join_new_line(t_lexer *lexer);
t_token			*new_quote_token(t_lexer *lexer, t_tokentype type);
bool			is_word_token(t_tokentype type);
void			add_heredoc_delimiter(t_lexer *lexer);
bool			read_heredoc(t_lexer *lexer, t_list *env_list);
void			print_kvs(t_list *kvs);
bool			is_metachar(const char c);
void			word_split(t_list *lst);
void			expand_quote(void *input);
char			*expand_quote_str(const char *str);
bool			is_valid_tokens(t_list *token_list);
t_lexer_product	*analyze_lex(const char *line, t_list *env);

// helper
t_token			*token_dup(t_token *token);
char			*replace_string(char *str, const char *from, const char *to);
char			*expand_single_envvar(char *str, const char *from,
					const char *to, size_t *i);
char			*expand_envvar_str(const char *input, void *env);
void			expand_envvar(t_list *lst, t_list *env_lst);
void			join_line_to_buffer(char **buffer, char **line);

char			*get_tmpfile_name(char *suffix);
void			write_tmpfile(char *tmpfile, char *buf);
void			create_tmpfile(char *tmpfile);
void			write_heredocs(t_lexer *lexer, char *buf, char *delimiter);
void			register_heredocs(t_lexer *lexer, char *delimiter);
void			delete_str(char **str);
void			ft_lstadd_next(t_list *lst, void *content);
bool			has_only_whitespace(const char *str);
bool			has_whitespace(const char *str);
void			update_flag(char c, bool *in_sq, bool *in_dq);
bool			is_word_char(char c);
char			*get_word(char *str);

#endif

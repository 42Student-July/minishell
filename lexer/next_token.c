#include "lexer.h"
#include "libft.h"

t_token	*next_token(t_lexer *lexer)
{
	t_token	*token;

	skip_whitespace(lexer);
	if (lexer->ch == '\0')
		token = new_token(TOKEN_EOF, NULL);
	else if (lexer->ch == '>')
	{
		if (peek_char(lexer) == '>')
		{
			read_char(lexer);
			token = new_token(TOKEN_REDIRECT_APPEND, ">>");
		}
		else
			token = new_token(TOKEN_REDIRECT_OUT, ">");
	}
	else if (lexer->ch == '<')
	{
		if (peek_char(lexer) == '<')
		{
			read_char(lexer);
			token = new_token(TOKEN_HEREDOC, "<<");
			add_heredoc_delimiter(lexer);
			return (token);
		}
		else
			token = new_token(TOKEN_REDIRECT_IN, "<");
	}
	else if (lexer->ch == '|')
		token = new_token(TOKEN_PIPE, "|");
	else if (!ft_isspace(lexer->ch))
		return (new_ident_token(lexer));
	else
		token = new_token(TOKEN_ILLEGAL, NULL);
	read_char(lexer);
	return (token);
}

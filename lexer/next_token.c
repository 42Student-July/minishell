#include "lexer.h"
#include "libft.h"

t_token *next_token(t_lexer *lexer)
{
	t_token *token;

	skip_whitespace(lexer);
	if (lexer->ch == '\0')
		token = new_token(TOKEN_EOF, NULL);
	else if (lexer->ch == '=')
		token = new_token(TOKEN_ASSIGN, "=");
	else if (lexer->ch == '\'')
		token = new_token(TOKEN_SQUOTE, "'");
	else if (lexer->ch == '"')
		token = new_token(TOKEN_DQUOTE, "\"");
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
		}
		else
			token = new_token(TOKEN_REDIRECT_IN, "<");
	}
	else if (lexer->ch == '|')
		token = new_token(TOKEN_PIPE, "|");
	else if (lexer->ch == '$')
	{
		if (peek_char(lexer) == '?')
		{
			read_char(lexer);
			token = new_token(TOKEN_EXIT_STATUS, "$?");
		}
		else
			return (new_env_token(lexer));
	}
	else if (ft_isspace(lexer->ch))
		token = new_token(TOKEN_WHITESPACE, " ");
	else if (ft_isletter(lexer->ch) || lexer->ch == '.' || lexer->ch == '-' || lexer->ch == '~' ||  lexer->ch == '/')
		return (new_ident_token(lexer));
	else
		token = new_token(TOKEN_ILLEGAL, NULL);
	read_char(lexer);
	return (token);
}

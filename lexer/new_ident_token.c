#include "lexer.h"
#include "libft.h"


t_token *new_ident_token(t_lexer *lexer)
{
	char *ident;
	t_token *token;
	const size_t pos = lexer->position;

	while (ft_isletter(lexer->ch) || lexer->ch == '.' || lexer->ch == '-' || lexer->ch == '~' ||  lexer->ch == '/')
		read_char(lexer);
	ident = ft_substr(lexer->input, pos, lexer->position - pos);
	token = new_token(TOKEN_IDENT, ident);
	free(ident);
	ident = NULL;
	return (token);
}

#include "libft.h"
#include "lexer.h"

t_token *new_env_token(t_lexer *lexer)
{
	char *ident;
	t_token *token;
	const size_t pos = lexer->position;

	read_char(lexer);
	while (ft_isletter(lexer->ch))
		read_char(lexer);
	ident = ft_substr(lexer->input, pos, lexer->position - pos);
	token = new_token(TOKEN_ENV, ident);
	free(ident);
	ident = NULL;
	return (token);
}

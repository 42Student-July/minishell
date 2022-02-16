#include "common.h"
#include "lexer.h"
#include "libft.h"

t_token	*new_ident_token(t_lexer *lexer)
{
	char	*ident;
	t_token	*token;
	size_t	pos;

	pos = lexer->position;
	while (!ft_isspace(lexer->ch) && lexer->ch != '\0' && lexer->ch != '\'' && lexer->ch != '"')
	{
		if (is_forbidden_char(lexer->ch))
		{
			ft_putendl_fd("forbidden char", STDERR);
			exit(EXIT_FAILURE);
		}
		read_char(lexer);
	}
	ident = ft_substr(lexer->input, pos, lexer->position - pos);
	token = new_token(TOKEN_IDENT, ident);
	free(ident);
	ident = NULL;
	return (token);
}

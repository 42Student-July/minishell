#include "lexer.h"
#include "libft.h"

t_token	*new_ident_token(t_lexer *lexer)
{
	char	*ident;
	t_token	*token;
	size_t	pos;
	char	c;

	pos = lexer->position;
	c = 0;
	while (!is_metachar(lexer->ch) && lexer->ch != '\0')
	{
		if (lexer->ch == '"' || lexer->ch == '\'')
		{
			c = lexer->ch;
			read_char(lexer);
			while (lexer->ch != c)
			{
				if (lexer->ch == '\0')
				{
					if (!join_new_line(lexer))
						exit(EXIT_FAILURE);
				}
				read_char(lexer);
			}
		}
		read_char(lexer);
	}
	ident = ft_substr(lexer->input, pos, lexer->position - pos);
	token = new_token(TOKEN_IDENT, ident);
	free(ident);
	ident = NULL;
	return (token);
}

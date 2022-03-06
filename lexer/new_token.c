#include "lexer.h"
#include "libft.h"
#include <stdio.h>

t_token	*new_token(t_tokentype type, char *literal)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		exit(EXIT_FAILURE);
	token->type = type;
	token->literal = ft_strdup(literal);
	return (token);
}

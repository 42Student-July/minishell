#include "lexer.h"
#include "libft.h"
#include <stdio.h>

t_token	*token_dup(t_token *token)
{
	t_token	*token_new;

	token_new = (t_token *)malloc(sizeof(t_token));
	if (token_new == NULL)
		exit(EXIT_FAILURE);
	token_new->type = token->type;
	token_new->literal = ft_strdup(token->literal);
	return (token_new);
}

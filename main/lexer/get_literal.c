#include "common.h"
#include "lexer.h"
#include "libft.h"

char *get_literal(t_token *token)
{
	if (token->type == TOKEN_IDENT)
		return (ft_strdup(token->literal));
	else
		exit(EXIT_FAILURE);
}

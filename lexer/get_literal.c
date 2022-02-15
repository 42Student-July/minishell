#include "common.h"
#include "lexer.h"
#include "libft.h"

char	*get_literal(t_token *token)
{
	if (is_word_token(token->type))
		return (ft_strdup(token->literal));
	else
		exit(EXIT_FAILURE);
}

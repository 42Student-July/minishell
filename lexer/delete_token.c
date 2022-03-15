#include "lexer.h"

void	delete_token(void *token)
{
	t_token	*tmp_token;

	tmp_token = (t_token *)token;
	free(tmp_token->literal);
	tmp_token->literal = NULL;
	free(tmp_token);
	tmp_token = NULL;
	return ;
}

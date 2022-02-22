#include "lexer.h"

bool is_valid_tokens(t_list *token_list)
{
	while (token_list != NULL)
	{
		if (((t_token *)token_list->content)->type == TOKEN_ILLEGAL)
			return (false);
		token_list = token_list->next;
	}
	return (true);
}

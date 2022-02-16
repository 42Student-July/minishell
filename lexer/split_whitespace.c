#include "lexer.h"

static bool	is_joinable_token(t_token *token)
{
	return (token->type == TOKEN_IDENT || token->type == TOKEN_DQUOTE ||
			token->type == TOKEN_SQUOTE);
}

// split by whitespace token
// if no whitespace, join token
// don't care about envvars because they have been expanded
void	split_whitespace(t_lexer_product *l_product)
{
	t_list	*token_list;
	t_list	*lst_next;
	t_token *token;
	char *joined_string;

	token_list = l_product->token_list;
	while (((t_token *)token_list->content)->type != TOKEN_EOF)
	{
		lst_next = token_list->next;
		token = (t_token *)token_list->content;
		if (is_joinable_token(token) && is_joinable_token(lst_next->content))
		{
			joined_string = ft_strjoin(token->literal, ((t_token *)lst_next->content)->literal);
			free(token->literal);
			token->literal = joined_string;
			token_list->next = lst_next->next;
			ft_lstdelone(lst_next, free);
			continue;
		}
		token_list = token_list->next;
	}
}

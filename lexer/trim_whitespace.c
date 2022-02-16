#include "libft.h"
#include "lexer.h"

void	trim_whitespace(t_lexer_product *l_product)
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
		if (((t_token *)lst_next->content)->type == TOKEN_WHITESPACE)
		{
			token->literal = joined_string;
			token_list->next = lst_next->next;
			ft_lstdelone(lst_next, free);
		}
		token_list = token_list->next;
	}
}


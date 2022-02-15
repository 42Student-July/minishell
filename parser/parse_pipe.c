#include "common.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"

t_list *parse_pipe(t_list *token_list, t_list **heredocs)
{
	t_list *left_tokens;
	t_list *right_tokens;
	t_token *token;
	t_list *lst;

	left_tokens = token_list;
	while (token_list != NULL)
	{
		token = token_list->content;
		if (token->type == TOKEN_EOF)
			break;
		if (token->type == TOKEN_PIPE)
		{
			right_tokens = token_list->next;
			if (right_tokens == NULL)
				return (NULL);
			lst = parse_pipe(right_tokens, heredocs);
			ft_lstadd_front(&lst, ft_lstnew(parse_redirect(left_tokens, heredocs)));
			return (lst);
		}
		token_list = token_list->next;
	}
	return (ft_lstnew(parse_redirect(left_tokens, heredocs)));
}

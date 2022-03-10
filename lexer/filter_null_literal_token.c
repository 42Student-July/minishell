#include "lexer.h"

static int	is_null_literal(t_token *token)
{
	return ((token->type == TOKEN_IDENT && token->literal != NULL)
			|| token->type != TOKEN_IDENT);
}

static void	skip_null_literal(t_token **token, t_list **lst)
{
	while (*lst)
	{
		*token = (*lst)->content;
		if (is_null_literal(*token))
			break ;
		*lst = (*lst)->next;
	}
}

static void
	copy_except_null(t_token **token, t_list **now, t_list **lst, t_list **res)
{
	t_list	*tmp;

	while ((*lst)->next != NULL)
	{
		*token = (*lst)->next->content;
		if (is_null_literal(*token))
		{
			tmp = ft_lstnew(token_dup(*token));
			if (tmp == NULL)
			{
				ft_lstclear(res, delete_token);
				return ;
			}
			(*now)->next = tmp;
			(*now) = (*now)->next;
			(*lst) = (*lst)->next;
		}
		else
			(*lst) = (*lst)->next;
	}
}

t_list	*filter_null_literal_token(t_list *lst)
{
	t_list	*res;
	t_list	*now;
	t_token	*token;

	if (lst == NULL)
		return (NULL);
	skip_null_literal(&token, &lst);
	now = ft_lstnew(token_dup(lst->content));
	if (now == NULL)
		return (NULL);
	res = now;
	copy_except_null(&token, &now, &lst, &res);
	return (res);
}

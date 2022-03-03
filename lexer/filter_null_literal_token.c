#include "lexer.h"

t_list	*filter_null_literal_token(t_list *lst)
{
	t_list	*res;
	t_list	*now;
	t_list	*tmp;
	t_token	*token;

	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		token = lst->content;
		if ((token->type == TOKEN_IDENT && token->literal != NULL) || token->type != TOKEN_IDENT)
			break ;
		lst = lst->next;
	}
	now = ft_lstnew(token_dup(lst->content));
	if (now == NULL)
		return (NULL);
	res = now;
	while (lst->next != NULL)
	{
		token = lst->next->content;
		if ((token->type == TOKEN_IDENT && token->literal != NULL) || token->type != TOKEN_IDENT)
		{
			tmp = ft_lstnew(token_dup(token));
			if (tmp == NULL)
			{
				ft_lstclear(&res, delete_token);
				return (res);
			}
			now->next = tmp;
			now = now->next;
			lst = lst->next;
		}
		else
		{
			lst = lst->next;
		}
	}
	return (res);
}

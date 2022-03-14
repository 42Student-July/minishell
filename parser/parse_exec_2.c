#include "lexer.h"
#include "libft.h"

void	skip_to_null(t_list **lst, char	**literal)
{
	while (*lst)
	{
		literal = (*lst)->content;
		if (literal != NULL)
			break ;
		*lst = (*lst)->next;
	}
}

t_list	*copy_except_null(t_list *lst, t_list *now, char *literal)
{
	t_list	*res;
	t_list	*tmp;

	res = now;
	while (lst->next != NULL)
	{
		literal = lst->next->content;
		if (literal != NULL)
		{
			tmp = ft_lstnew(ft_strdup(literal));
			if (tmp == NULL)
			{
				ft_lstclear(&res, free);
				return (res);
			}
			now->next = tmp;
			now = now->next;
			lst = lst->next;
		}
		else
			lst = lst->next;
	}
	return (res);
}

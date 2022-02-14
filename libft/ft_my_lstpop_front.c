#include "libft.h"

t_list	*ft_my_lstpop_front(t_list **lst)
{
	t_list	*top;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	top = *lst;
	*lst = (*lst)->next;
	top->next = NULL;
	return (top);
}

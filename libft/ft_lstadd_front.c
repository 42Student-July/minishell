
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_elm)
{
	if (lst == NULL || new_elm == NULL)
		return ;
	ft_lstlast(new_elm)->next = (*lst);
	(*lst) = new_elm;
}

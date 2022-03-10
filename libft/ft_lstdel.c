
#include "libft.h"

bool	ft_lstdel(t_list *lst, t_list *target)
{
	if (lst == NULL || target == NULL)
		return (false);
	while (lst->next != NULL)
	{
		if (lst->next == target)
		{
			lst->next = target->next;
			free(target);
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:31:34 by mhirabay          #+#    #+#             */
/*   Updated: 2021/12/03 13:20:34 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_lst	*ft_lstmap(t_lst *lst, int (*f)(void *), void (*del)(void *))
{
	t_lst	*new_list;
	t_lst	*tmp;

	if (!lst || !f)
		return (NULL);
	new_list = ft_lstnew(f((void *)lst));
	if (new_list == NULL)
	{
		ft_lstclear(&new_list, del);
		return (NULL);
	}
	tmp = new_list;
	lst = lst->next;
	while (lst)
	{
		tmp->next = ft_lstnew(f((void *)lst));
		if (!tmp->next)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	return (new_list);
}

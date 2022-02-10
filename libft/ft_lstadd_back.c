/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:24:36 by akito             #+#    #+#             */
/*   Updated: 2022/02/10 10:16:29 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_lstadd_back(t_list **lst, t_list *new_elm)
{
	t_list	*list;

	if (lst == NULL || new_elm == NULL)
		return (false);
	if (*lst == NULL)
		*lst = new_elm;
	else
	{
		list = ft_lstlast(*lst);
		list->next = new_elm;
	}
	return (true);
}

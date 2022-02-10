/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:24:36 by akito             #+#    #+#             */
/*   Updated: 2022/01/31 23:43:54 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_elm)
{
	t_list	*list;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_elm;
		return ;
	}
	list = ft_lstlast(*lst);
	list->next = new_elm;
}

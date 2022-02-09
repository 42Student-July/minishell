/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:24:39 by akito             #+#    #+#             */
/*   Updated: 2022/01/31 23:44:05 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_elm)
{
	if (lst == NULL || new_elm == NULL)
		return ;
	ft_lstlast(new_elm)->next = (*lst);
	(*lst) = new_elm;
}

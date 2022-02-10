/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:30:27 by mhirabay          #+#    #+#             */
/*   Updated: 2021/12/03 13:10:06 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	if (lst == NULL || new == NULL)
		return (false);
	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
	return (true);
}

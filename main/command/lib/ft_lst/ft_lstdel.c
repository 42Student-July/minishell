/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:47:53 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/08 10:53:23 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstdel(t_lst *lst, t_lst *target)
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


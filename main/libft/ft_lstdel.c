/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:47:53 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 10:14:22 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

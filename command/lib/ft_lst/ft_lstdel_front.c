/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:31:59 by mhirabay          #+#    #+#             */
/*   Updated: 2021/12/03 17:54:52 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstdel_front(t_lst **lst)
{	
	t_lst	*tmp;

	if (lst == NULL)
		return (false);
	tmp = (*lst)->next;
	free(*lst);
	*lst = tmp;
	return (true);
}

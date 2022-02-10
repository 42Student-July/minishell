/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:31:30 by mhirabay          #+#    #+#             */
/*   Updated: 2021/12/03 12:14:08 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_lst	*ft_lstlast(t_lst *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

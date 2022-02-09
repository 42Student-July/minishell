/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:31:27 by mhirabay          #+#    #+#             */
/*   Updated: 2021/12/03 13:19:02 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstiter(t_lst *lst, t_content_f f)
{

	if (lst == NULL || f == NULL)
		return (false);
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
	return (true);
}

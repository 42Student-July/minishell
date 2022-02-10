/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:31:37 by mhirabay          #+#    #+#             */
/*   Updated: 2021/12/03 12:16:03 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*new_list;

	new_list = (t_lst *)malloc(sizeof(t_lst));
	if (new_list == NULL)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

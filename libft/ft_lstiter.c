/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito <akito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:24:47 by akito             #+#    #+#             */
/*   Updated: 2021/09/09 18:24:48 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	ft_lstiter_with_var(t_list *lst, void (*f)(void *, void *), void *var)
{
	if (f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content, var);
		lst = lst->next;
	}
}

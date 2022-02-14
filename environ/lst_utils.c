/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:27:06 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/14 21:28:59 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

bool	swap_lst_content(t_list *a, t_list *b)
{
	void	*tmp;

	if (a == NULL || b == NULL)
		return (false);
	if (a->content == b->content)
	{
		return (true);
	}
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (true);
}

void	sort_listkey_by_ascii(t_list *lst)
{
	// 大文字アルファベット → _ → 小文字のアルファベットに並び替える
	t_list	*min;

	while (lst->next != NULL)
	{
		min = get_list_by_min_ascii_key(lst);
		swap_lst_content(lst, min);
		lst = lst->next;
	}
}

t_list	*get_list_by_key(t_list *lst, char *key)
{
	t_list	*ret;

	ret = lst;
	while (ret != NULL)
	{
		if (is_same_str(get_key(ret->content), key))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

t_list	*get_list_by_min_ascii_key(t_list *lst)
{
	t_list	*tmp;
	char	*min_key;
	char	*next_key;

	tmp = lst;
	while (lst->next != NULL)
	{
		min_key = get_key(tmp->content);
		next_key = get_key(lst->next->content);
		// lvalueの方が大きいので、tmpをrvalueにchange
		if (is_lvalue_bigger_ascii(min_key, next_key))
			tmp = lst->next;
		lst = lst->next;
	}
	return (tmp);
}

void	del_lst_by_key(t_list *lst, char *key)
{
	t_list	*tmp;

	tmp = get_list_by_key(lst, key);
	ft_lstdel(lst, tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:44:59 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/23 17:00:36 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

bool	update_value(t_list *lst, char *key, char *new_v, t_exec_attr *ea)
{
	t_list	*target;
	char	*tmp;

	if (new_v == NULL)
		// もしnewがnullだったら値は更新しない。
		return (true);
	target = get_lst_by_key(lst, key);
	if (target == NULL)
	{
		printf("invalid key\n");
		return (false);
	}
	tmp = ft_strdup(new_v);
	if (tmp == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	ft_kvsreplace_value(target->content, tmp);
	return (true);
}

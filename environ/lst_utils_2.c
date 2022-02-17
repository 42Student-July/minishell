/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:44:59 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/17 16:00:29 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

bool	update_value(t_list *lst, char *key, char *new_v, t_exec_attr *ea)
{
	t_list	*target;
	char	*current_v;

	target = get_list_by_key(lst, key);
	if (target == NULL)
	{
		printf("invalid key\n");
		return (false);
	}
	current_v = ft_kvsget_value(target->content);

	if (current_v == new_v)
	{
		// TODO: あとでけす
		printf("new value equals current value\n");
		return (true);
	}
	free(current_v);
	current_v = ft_strdup(new_v);
	if (current_v == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	return (true);
}

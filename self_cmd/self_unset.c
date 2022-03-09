/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:19:55 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/09 17:41:41 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

int	exec_self_unset(t_cmd *cmd, t_exec_attr *ea)
{
	t_list	*lst;
	char	*arg;
	int		exit_status;

	exit_status = true;
	lst = cmd->args->next;
	while (lst != NULL)
	{
		arg = (char *)(lst->content);
		if (arg == NULL)
			return (1);
		if (is_invalid_name(arg))
		{
			exit_status = false;
			print_error_msg_with_var(UNSET, arg);
		}
		del_lst_by_key(ea->env_lst, arg);
		del_lst_by_key(ea->export_lst, arg);
		if (is_same_str(arg, "PWD"))
		{
			ea->current_pwd = ft_strdup("");
			if (ea->current_pwd == NULL)
				abort_minishell(MALLOC_ERROR, ea);
		}
		lst = lst->next;
	}
	if (exit_status)
		return (0);
	return (1);
}

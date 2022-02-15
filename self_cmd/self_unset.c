/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:19:55 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/15 09:33:03 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	exec_self_unset(t_exec_attr *ea)
{
	// envlstとexportlstから対象の文字列を削除
	(void)ea;
	if (get_cmd_arg(ea->cmd, ea) == NULL)
		return ;
	if (is_invalid_name(get_cmd_arg(ea->cmd, ea)))
		print_error_msg_with_var(UNSET, get_cmd_arg(ea->cmd, ea));
	del_lst_by_key(ea->env_lst, get_cmd_arg(ea->cmd, ea));
	del_lst_by_key(ea->export_lst, get_cmd_arg(ea->cmd, ea));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:19:55 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/09 15:48:09 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

void	exec_self_unset(t_exec_attr *ea)
{
	// envlstとexportlstから対象の文字列を削除
	if (ea->command[CMD_ARG] == NULL)
		return ;
	if (is_invalid_name(ea->command[CMD_ARG]))
		print_error_msg_with_var(UNSET, ea->command[CMD_ARG]);
	del_lst_by_key(ea->env_lst, ea->command[CMD_ARG]);
	del_lst_by_key(ea->export_lst, ea->command[CMD_ARG]);
}

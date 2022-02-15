/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:18 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/15 09:47:29 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// 引数のコマンド名と実行時のコマンドが一致していたらtrue
bool	is_(char *command, char *cmd)
{
	if (is_same_str(cmd, command))
		return (true);
	return (false);
}

void	execute_self_cmd(t_list	*cmd, t_exec_attr *ea)
{
	if (is_redirect_flag(ea))
		change_direction(ea);
	if (is_(CD, get_cmd_name(cmd)))
		exec_self_cd(ea);
	else if (is_(EXPORT, get_cmd_name(cmd)))
		exec_self_export(ea);
	else if (is_(EXIT, get_cmd_name(cmd)))
		exec_self_exit(ea);
	else if (is_(UNSET, get_cmd_name(cmd)))
		exec_self_unset(ea);
	else if (is_(PWD, get_cmd_name(cmd)))
		exec_self_pwd(ea);
	else if (is_(ECHO, get_cmd_name(cmd)))
		exec_self_echo(ea);
	else if (is_(ENV, get_cmd_name(cmd)))
		exec_self_env(ea);
}

// TODO: is_関数を使う
bool	is_self_cmd(char *cmd)
{
	if (is_(CD, cmd))
		return (true);
	if (is_(EXPORT, cmd))
		return (true);
	if (is_(EXIT, cmd))
		return (true);
	if (is_(UNSET, cmd))
		return (true);
	if (is_(PWD, cmd))
		return (true);
	if (is_(ECHO, cmd))
		return (true);
	if (is_(ENV, cmd))
		return (true);
	return (false);
}

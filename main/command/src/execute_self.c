/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_self.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:18 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/10 12:20:33 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

// 引数のコマンド名と実行時のコマンドが一致していたらtrue
bool	is_(const char *command, t_exec_attr *ea)
{
	if (ft_strncmp(ea->command[CMD_NAME], command, ft_strlen(command)) == 0)
		return (true);
	return (false);
}

void	execute_self(t_exec_attr *ea)
{
	if (is_redirect_flag(ea))
		change_direction(ea);
	if (is_(CD, ea))
		exec_self_cd(ea);
	else if (is_(EXPORT, ea))
		exec_self_export(ea);
	else if (is_(EXIT, ea))
		exec_self_exit(ea);
	else if (is_(UNSET, ea))
		exec_self_unset(ea);
	else if (is_(PWD, ea))
		exec_self_pwd(ea);
	else if (is_(ECHO, ea))
		exec_self_echo(ea);
	else if (is_(ENV, ea))
		exec_self_env(ea);
}

// TODO: is_関数を使う
bool	is_self_cmd(const char *c)
{
	size_t	c_len;

	c_len = ft_strlen(c);
	if (ft_strncmp(c, CD, c_len) == 0)
		return (true);
	if (ft_strncmp(c, ECHO, c_len) == 0)
		return (true);
	if (ft_strncmp(c, PWD, c_len) == 0)
		return (true);
	if (ft_strncmp(c, EXIT, c_len) == 0)
		return (true);
	if (ft_strncmp(c, EXPORT, c_len) == 0)
		return (true);
	if (ft_strncmp(c, ENV, c_len) == 0)
		return (true);
	if (ft_strncmp(c, UNSET, c_len) == 0)
		return (true);
	return (false);
}

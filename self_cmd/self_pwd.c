/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:57 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/19 17:42:40 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

char	*x_getcwd(t_exec_attr *ea)
{
	char	*pathname;

	// TODO: getcwdは一応残しておく
	// pathname = getcwd(NULL, 0);
	// if (pathname == NULL)
	// {
		// pathnameがnullの場合、環境変数のPWDからとってきて表示する
		pathname = ft_kvsget_value(get_lst_by_key(ea->env_lst, "PWD")->content);
	// }
	return (pathname);
}

int	exec_self_pwd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*pathname;

	(void)cmd;
	pathname = x_getcwd(ea);
	ft_putstr_fd(pathname, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

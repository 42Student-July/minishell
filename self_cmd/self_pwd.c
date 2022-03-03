/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:57 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/01 13:35:09 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

char	*x_getcwd(t_exec_attr *ea)
{
	char	*pathname;
	t_list	*lst;

	lst = get_lst_by_key(ea->env_lst, "PWD");
	if (lst == NULL)
		return (NULL);
	pathname = ft_kvsget_value(lst->content);
	// PWDが空文字のときはea->current_pwdを使用する
	if (ft_strlen(pathname) == 0)
		return (NULL);
	return (pathname);
}

int	exec_self_pwd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*pathname;

	(void)cmd;
	pathname = x_getcwd(ea);
	if (pathname == NULL)
		pathname = ea->current_pwd;
	ft_putstr_fd(pathname, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

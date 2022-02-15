/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:35:12 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/15 17:25:00 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	exec_self_echo(t_cmd *cmd, t_exec_attr *ea)
{
	(void)cmd;
	ft_putstr_fd(get_cmd_arg(ea->cmd_lst, ea), STDOUT_FILENO);
}

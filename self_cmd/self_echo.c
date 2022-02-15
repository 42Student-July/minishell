/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:35:12 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/15 14:04:18 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	exec_self_echo(t_exec_attr *ea)
{
	(void)ea;
	ft_putstr_fd(get_cmd_arg(ea->cmd_lst, ea), STDOUT_FILENO);
}

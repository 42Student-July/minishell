/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:35:12 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/09 14:35:19 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

void	exec_self_echo(t_exec_attr *ea)
{
	ft_putstr_fd(ea->command[1], STDOUT_FILENO);
}

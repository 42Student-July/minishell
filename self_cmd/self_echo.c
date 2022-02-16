/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:35:12 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/16 09:54:02 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	exec_self_echo(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;

	argv_one = get_argv_one(cmd);
	if (argv_one == NULL)
		return ;
	(void)ea;
	// TODO: pipeでつないだときへの対応、引数が2つの場合にも対応
	ft_putstr_fd(argv_one, STDOUT_FILENO);
}

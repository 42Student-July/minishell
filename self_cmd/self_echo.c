/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:35:12 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/18 00:33:04 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

int	exec_self_echo(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;

	argv_one = get_argv_one(cmd);
	if (argv_one == NULL)
		return (1);
	(void)ea;
	// TODO: pipeでつないだときへの対応、引数が2つの場合にも対応
	ft_putstr_fd(argv_one, STDOUT_FILENO);
	return (0);
}

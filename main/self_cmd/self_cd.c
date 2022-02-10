/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:54 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/10 14:27:22 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

static void	x_chdir(const char *path)
{
	if (chdir(path) == -1)
	{
		// TODO:いい感じのエラーメッセージを追加する
		// printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	exec_self_cd(t_exec_attr *ea)
{
	x_chdir(ea->command[DIR]);
}

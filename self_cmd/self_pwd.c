/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:57 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/15 17:30:28 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

static void	x_getcwd(char *pathname, int bufsiz)
{
	if (getcwd(pathname, bufsiz) == NULL)
	{
		// TODO:いい感じのエラーメッセージを追加する
		// printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	exec_self_pwd(t_exec_attr *ea)
{
	char	pathname[BUFSIZ];

	(void)ea;
	x_getcwd(pathname, BUFSIZ);
	ft_putstr_fd(pathname, STDOUT_FILENO);
}

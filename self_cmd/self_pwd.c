/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:57 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/18 00:32:22 by tkirihar         ###   ########.fr       */
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

int	exec_self_pwd(t_cmd *cmd, t_exec_attr *ea)
{
	char	pathname[PATH_MAX];

	(void)cmd;
	(void)ea;
	x_getcwd(pathname, PATH_MAX);
	ft_putstr_fd(pathname, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

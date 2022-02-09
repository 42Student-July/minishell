/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:57 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/09 14:35:50 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

static void	x_getcwd(char *pathname, int bufsiz)
{
	if (getcwd(pathname, bufsiz) == NULL)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	exec_self_pwd(t_exec_attr *ea)
{
	char	pathname[BUFSIZ];

	(void)ea;
	x_getcwd(pathname, BUFSIZ);
	printf("%s\n", pathname);
}

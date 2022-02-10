/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 11:06:22 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	execute_cmd(t_list *cmd)
{
	t_exec_attr	*e_attr;

	(void)cmd;
	int argc = 0;
	const char **argv = NULL;
	init(&e_attr);
	create_cmd_from_arg(argc, argv, e_attr);
	if (is_self_cmd(argv[1]))
		execute_self(e_attr);
	else
		execute_builtin(e_attr);
	return (0);
}

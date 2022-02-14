/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/14 16:52:08 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	execute_cmd(t_exec_attr *ea)
{
	int			pipe_cnt;
	// t_exec_attr	*ea;

	printf("start execute_cmd\n");
	
	// (void)ea;
	// init_new(&ea, cmd);
	// print_all_env_lst(ea);
	print_all_export_lst(ea);
	pipe_cnt = ft_lstsize(ea->cmd) - 1;
	if (pipe_cnt == 0)
	{
		no_pipe_process(ea->cmd);
	}
	else
	{
		pipe_process(ea->cmd, pipe_cnt);
	}
	return (0);
}

// int	execute_cmd(t_list *cmd)
// {
// 	t_exec_attr	*e_attr;

// 	(void)cmd;
// 	int argc = 0;
// 	const char **argv = NULL;
// 	init(&e_attr);
// 	create_cmd_from_arg(argc, argv, e_attr);
// 	if (is_self_cmd(argv[1]))
// 		execute_self(e_attr);
// 	else
// 		execute_builtin(e_attr);
// 	return (0);
// }

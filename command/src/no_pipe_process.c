/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:23:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/14 22:11:29 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	do_execute_cmd(t_exec_attr *ea)
{
	pid_t	pid;
	int		status;
	char	**cmdv;
	char	*cmd_path;

	cmdv = convert_lst_to_argv(get_exec_cmd(ea)->args);
	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		cmd_path = find_path(ea->cmd->content, ea);
		// printf("cmd_path : %s\n", cmd_path);
		if (execve(cmd_path, cmdv, NULL) == -1)
		{
			printf("exec error\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		pid = wait(&status);
		if (pid == -1)
			printf("cprocess error\n");
	}
}

void	no_pipe_process(t_exec_attr *ea)
{
	do_execute_cmd(ea);
}

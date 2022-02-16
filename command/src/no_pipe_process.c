/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:23:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/16 14:05:33 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	execute_ext_cmd(t_cmd *c, t_exec_attr *ea)
{
	pid_t	pid;
	int		status;
	char	**cmdv;
	char	*cmd_path;
	char	**environ;

	cmdv = convert_lst_to_argv(c->args);
	cmd_path = find_path(c->cmd, ea);
	if (cmd_path == NULL)
	{
		printf("%s: command not found\n", c->cmd);
		return ;
	}
	environ = convert_envlst_to_array(ea);
	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		if (execve(cmd_path, cmdv, environ) == -1)
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
	t_cmd *c;
	
	c = get_cmd(ea);
	// TODO: コマンドが存在しない時、ここでsegvする
	if (ea->cmd_lst == NULL)
		return ;
	if (is_self_cmd(c->cmd))
		execute_self_cmd(c, ea);
	else
		execute_ext_cmd(c, ea);
}

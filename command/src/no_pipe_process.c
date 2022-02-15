/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:23:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/11 16:33:36 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	do_execute_cmd(t_cmd *rc)
{
	pid_t	pid;
	int		status;
	char	**cmdv;
	char	*cmd_path;

	cmdv = convert_arglst_to_array(rc);
	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		cmd_path = ft_strjoin("/bin/", cmdv[0]);
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

void	no_pipe_process(t_list *cmd)
{
	do_execute_cmd(cmd->content);
}

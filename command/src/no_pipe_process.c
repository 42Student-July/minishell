/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:23:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/14 23:33:56 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	execute_ext_cmd(t_exec_attr *ea)
{
	pid_t	pid;
	int		status;
	char	**cmdv;
	char	*cmd_path;
	char	**environ;

	cmdv = convert_lst_to_argv(get_exec_cmd(ea)->args);
	cmd_path = find_path(ea->cmd->content, ea);
	environ = convert_envlst_to_array(ea->env_lst);
	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
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

void	execute_self_cmd(t_exec_attr *ea)
{
	if (is_(CD, ea))
		exec_self_cd(ea);
	else if (is_(EXPORT, ea))
		exec_self_export(ea);
	else if (is_(EXIT, ea))
		exec_self_exit(ea);
	else if (is_(UNSET, ea))
		exec_self_unset(ea);
	else if (is_(PWD, ea))
		exec_self_pwd(ea);
	else if (is_(ECHO, ea))
		exec_self_echo(ea);
	else if (is_(ENV, ea))
		exec_self_env(ea);
}


void	no_pipe_process(t_exec_attr *ea)
{
	if (is_self_cmd(get_cmd(ea->cmd)))
		execute_self_cmd(ea);
	else
		execute_ext_cmd(ea);
}

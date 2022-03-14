/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 07:12:57 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/15 07:55:11 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	proceed_execve(t_cmd *c, char *cmd_path, t_exec_attr *ea)
{
	char	**cmdv;
	char	**environ;

	cmdv = convert_lst_to_argv(c->args);
	environ = convert_envlst_to_array(ea);
	if (is_dir(cmd_path))
	{
		ft_put_cmd_error(c->cmd, "is a directory");
		exit(126);
	}
	if (has_redirect_file(c))
		redirect(c, ea);
	if (execve(cmd_path, cmdv, environ) == -1)
		execve_error(errno, c->cmd);
}

void	proceed_wait(pid_t cpid)
{
	int		status;
	pid_t	wait_ret;

	while (true)
	{
		wait_ret = waitpid(cpid, &status, 0);
		if (wait_ret > 0)
			break ;
		if (WIFSIGNALED(status))
			continue ;
		exit(EXIT_FAILURE);
	}
	if (!WIFSIGNALED(status))
		g_exit_status = WEXITSTATUS(status);
}

void	execute_ext_cmd(t_cmd *c, t_exec_attr *ea)
{
	pid_t	cpid;
	char	*cmd_path;

	cmd_path = create_cmd_path(c, ea);
	if (cmd_path == NULL)
		return ;
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cpid == 0)
		proceed_execve(c, cmd_path, ea);
	else
	{
		free(cmd_path);
		proceed_wait(cpid);
	}
}

void	no_pipe_process(t_exec_attr *ea)
{
	t_cmd	*c;

	c = get_cmd(ea);
	ea->has_not_permission = malloc_has_not_permission(1);
	if (has_redirect_file(c))
		if (!open_files(c, ea))
			return (free(ea->has_not_permission));
	if (c->cmd == NULL)
		return (free(ea->has_not_permission));
	if (is_self_cmd(c->cmd))
	{
		if (has_redirect_file(c))
			redirect(c, ea);
		execute_self_cmd(c, ea, NO_PIPE);
		if (has_redirect_file(c))
			reset_stdfd(ea);
	}
	else
		execute_ext_cmd(c, ea);
	free(ea->has_not_permission);
}

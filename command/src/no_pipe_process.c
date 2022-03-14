/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 07:12:57 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/15 07:12:58 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "command.h"

bool	is_path(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

char *create_cmd_path(t_cmd *c, t_exec_attr *ea)
{
	char	*cmd_path;

	if (is_path(c->cmd))
		cmd_path = ft_xstrdup(c->cmd);
	else
	{
		cmd_path = find_path(c->cmd, ea, 0);
		if (cmd_path == NULL)
		{
			if (ea->has_not_permission[0])
			{
				ft_put_cmd_error(c->cmd, "Permission denied");
				g_exit_status = 126;
			}
			else
			{
				ft_put_cmd_error(c->cmd, "command not found");
				g_exit_status = 127;
			}
			return (NULL);
		}
	}
	return (cmd_path);
}

void	execute_ext_cmd(t_cmd *c, t_exec_attr *ea)
{
	pid_t	cpid;
	pid_t	wait_ret;
	int		status;
	char	**cmdv;
	char	*cmd_path;
	char	**environ;

	cmdv = convert_lst_to_argv(c->args);
	cmd_path = create_cmd_path(c, ea);
	if (cmd_path == NULL)
	{
		free_char_dptr(cmdv);
		return ;
	}
	environ = convert_envlst_to_array(ea);
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cpid == 0)
	{
		if (is_dir(cmd_path))
		{
			ft_put_cmd_error(c->cmd, "is a directory");
			exit(126);
		}
		if (has_redirect_file(c))
			redirect(c, ea);
		if (execve(cmd_path, cmdv, environ) == -1)
		{
			execve_error(errno, c->cmd);
		}
		free(cmd_path);
		free_char_dptr(cmdv);
		free_char_dptr(environ);
	}
	else
	{
		free(cmd_path);
		free_char_dptr(cmdv);
		free_char_dptr(environ);
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
}

void	no_pipe_process(t_exec_attr *ea)
{
	t_cmd *c;

	c = get_cmd(ea);
	ea->has_not_permission = malloc_has_not_permission(1);
	// fileのopenの処理はコマンドに関わらず行う
	if (has_redirect_file(c))
		if (!open_files(c, ea))
		{
			free(ea->has_not_permission);
			return ;
		}
	if (c->cmd == NULL)
	{
		free(ea->has_not_permission);
		return ;
	}
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

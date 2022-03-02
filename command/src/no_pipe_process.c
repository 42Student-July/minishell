/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:23:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/02 14:09:38 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "errno.h"

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

// bool	has_cmdpath_in_pathlst(char *cmdpath, char **pathlst, t_exec_attr *ea)
// {
// 	size_t	i;

// 	i = 0;
// 	while (path[i] == NULL)
// 	{
// 		i++;
// 	}

// }

// bool	path_exits(char *cmdpath, t_exec_attr *ea)
// {
// 	t_list	*lst;
// 	char	**pathlst;
// 	char	*envpath;

// 	lst = get_lst_by_key(ea->env_lst, "PATH");
// 	if (lst == NULL)
// 		return (NULL);
// 	envpath = ft_kvsget_value(lst->content);
// 	pathlst = ft_split(envpath, ':');
// 	if (pathlst == NULL)
// 		exit(EXIT_FAILURE);
// 	return (has_cmdpath_in_pathlst(cmdpath, pathlst, ea));
// }

// void	error_process(int cp_errno)
// {
// 	printf("errno %d\n", cp_errno);
// 	perror("execve");
// 	if (cp_errno == ENOENT)
// 	{
// 		g_exit_status = 127;
// 	}
// 	else if (cp_errno == )
// }

void	execute_ext_cmd(t_cmd *c, t_exec_attr *ea)
{
	pid_t	cpid;
	pid_t	wait_ret;
	int		status;
	char	**cmdv;
	char	*cmd_path;
	char	**environ;

	cmdv = convert_lst_to_argv(c->args);
	if (is_path(c->cmd))
	{
		cmd_path = ft_strdup(c->cmd);
		if (cmd_path == NULL)
		{
			printf("ft_strdup error\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd_path = find_path(c->cmd, ea);
		if (cmd_path == NULL)
		{
			ft_put_error("command not found", c->cmd);
			g_exit_status = 127;
			return ;
		}
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
		if (has_redirect_file(c))
			redirect(c, ea);
		if (execve(cmd_path, cmdv, environ) == -1)
		{
			perror("execve");
			// error_process(errno);
		}
	}
	else
	{
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
	// TODO: コマンドが存在しない時、ここでsegvする
	if (is_self_cmd(c->cmd))
	{
		if (has_redirect_file(c))
			redirect(c, ea);
		execute_self_cmd(c, ea);
		if (has_redirect_file(c))
			reset_stdfd(ea);
	}
	else
		execute_ext_cmd(c, ea);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:23:41 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/23 13:34:01 by tkirihar         ###   ########.fr       */
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
			printf("%s: command not found\n", c->cmd); // 標準エラー出力にする
			g_exit_status = 127;
			return ;
		}
	}
	environ = convert_envlst_to_array(ea);
	cpid = fork();
	if (cpid == -1)
		printf("fork error\n");
	else if (cpid == 0)
	{
		if (has_redirect_file(c))
			redirect(c, ea);
		if (execve(cmd_path, cmdv, environ) == -1)
		{
			printf("exec error\n");
			exit(EXIT_FAILURE);
		}
		// こっちはいらないかもしれないけど一応
		if (has_redirect_file(c))
			revert_direction(c, ea);
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
			revert_direction(c, ea);
	}
	else
		execute_ext_cmd(c, ea);
}

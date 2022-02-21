/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:07:42 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/21 20:05:21 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "errno.h"

int	**malloc_pipe_fd(int pipe_cnt)
{
	int	i;
	int	**pipe_fd;

	pipe_fd = (int **)malloc(sizeof(int *) * pipe_cnt);
	if (pipe_fd == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pipe_cnt)
	{
		pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe_fd[i] == NULL)
		{
			printf("malloc error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe_fd);
}

void	make_pipe(int cmd_i, int pipe_cnt, int **pipe_fd)
{
	if (cmd_i != pipe_cnt)
	{
		pipe(pipe_fd[cmd_i]);
	}
}

void	set_pipe_fd(int pipe_cnt, int cmd_i, int **pipe_fd)
{
	if (cmd_i == 0)
	{
		dup2(pipe_fd[cmd_i][PIPE_OUT], STDOUT_FILENO);
		close(pipe_fd[cmd_i][PIPE_IN]);
		close(pipe_fd[cmd_i][PIPE_OUT]);
	}
	else if (cmd_i == pipe_cnt)
	{
		dup2(pipe_fd[cmd_i - 1][PIPE_IN], STDIN_FILENO);
		close(pipe_fd[cmd_i - 1][PIPE_IN]);
		close(pipe_fd[cmd_i - 1][PIPE_OUT]);
	}
	else
	{
		dup2(pipe_fd[cmd_i - 1][PIPE_IN], STDIN_FILENO);
		dup2(pipe_fd[cmd_i][PIPE_OUT], STDOUT_FILENO);
		close(pipe_fd[cmd_i - 1][PIPE_IN]);
		close(pipe_fd[cmd_i - 1][PIPE_OUT]);
		close(pipe_fd[cmd_i][PIPE_IN]);
		close(pipe_fd[cmd_i][PIPE_OUT]);
	}
}

void	close_pipe(int **pipe_fd, int cmd_i)
{
	close(pipe_fd[cmd_i - 1][PIPE_IN]);
	close(pipe_fd[cmd_i - 1][PIPE_OUT]);
}

void	wait_process(int pipe_cnt, int *cpid_array)
{
	int		status;
	int		i;
	pid_t	pid;
	bool	is_EINTR;

	(void)cpid_array;
	i = 0;
	while (i < pipe_cnt + 1)
	{
		is_EINTR = false;
		while (true)
		{
			pid = waitpid(cpid_array[i], &status, 0);
			if (pid > 0)
				break ;
			if (errno == EINTR)
			{
				is_EINTR = true;
				continue ;
			}
			exit(EXIT_FAILURE);
		}
		if (!is_EINTR)
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}

// TODO:構造体がexec単位でわけられているので、eaを渡したくない
void	exec_cmd(t_cmd *c, t_exec_attr *ea, int cmd_i, int **pipe_fd, int *cpid_array)
{
	int		pid;
	char	**cmdv;
	char	*cmd_path;
	char	**environ;

	(void)ea->env_lst;
	cmdv = convert_lst_to_argv(c->args);
	environ = convert_envlst_to_array(ea);
	pid = fork();
	cpid_array[cmd_i] = pid;
	if (pid == -1)
	{
		printf("fork error\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		set_pipe_fd(ea->pipe_count, cmd_i, pipe_fd);
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
				exit(127);
			}
		}
		if (has_redirect_file(c))
			redirect(c, ea);
		if (is_self_cmd(c->cmd))
			execute_self_cmd(c, ea);
		if (execve(cmd_path, cmdv, environ) == -1)
		{
			printf("exec error\n");
			exit(EXIT_FAILURE);
		}
		exit(0);
	}
	else if (cmd_i > 0)
	{
		close_pipe(pipe_fd, cmd_i);
	}
}

void	free_pipe_fd(int **pipe_fd, int pipe_cnt)
{
	int	i;

	i = 0;
	while (i < pipe_cnt)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}

void	pipe_process(t_exec_attr *ea)
{
	int				cmd_i;
	int				**pipe_fd;
	t_cmd			*current_cmd;
	int				cpid_array[10];

	pipe_fd = malloc_pipe_fd(ea->pipe_count);
	cmd_i = 0;
	current_cmd = ea->cmd_lst->content;
	while (cmd_i < ea->pipe_count + 1)
	{
		make_pipe(cmd_i, ea->pipe_count, pipe_fd);
		exec_cmd(current_cmd, ea, cmd_i, pipe_fd, cpid_array);
		close_pipe(pipe_fd, cmd_i);
		cmd_i++;
		current_cmd = ea->cmd_lst->next->content;
	}
	wait_process(ea->pipe_count, cpid_array);
}

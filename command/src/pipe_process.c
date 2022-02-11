/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:07:42 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/11 03:47:08 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	**malloc_pipe_fd(int pipe_cnt)
{
	int	i;
	int	**pipe_fd;

	pipe_fd = (int **)malloc(sizeof(int) * pipe_cnt);
	if (pipe_fd == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pipe_cnt)
	{
		printf("malloc\n");
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

void	set_pipe_fd(int pipe_cnt, int cmd_i, int **pipe_fd)
{
	if (cmd_i == 0)
	{
		dup2(pipe_fd[cmd_i][1], 1);
		close(pipe_fd[cmd_i][1]);
		close(pipe_fd[cmd_i][0]);
	}
	else if (cmd_i == pipe_cnt)
	{
		dup2(pipe_fd[cmd_i - 1][0], 0);
		close(pipe_fd[cmd_i - 1][0]);
		close(pipe_fd[cmd_i - 1][1]);
	}
	else
	{
		dup2(pipe_fd[cmd_i - 1][0], 0);
		dup2(pipe_fd[cmd_i][1], 1);
		close(pipe_fd[cmd_i - 1][0]);
		close(pipe_fd[cmd_i - 1][1]);
		close(pipe_fd[cmd_i][0]);
		close(pipe_fd[cmd_i][1]);
	}
}

void	make_pipe(int cmd_i, int pipe_cnt, int **pipe_fd)
{
	if (cmd_i != pipe_cnt)
	{
		printf("%s %d\n", __FILE__, __LINE__);
		printf("%d\n", cmd_i);
		pipe(pipe_fd[cmd_i]);
	}
	printf("%s %d\n", __FILE__, __LINE__);
}

void	exec_cmd(t_redirect_cmd *rc, int pipe_cnt, int cmd_i, int **pipe_fd)
{
	int		pid;
	char	**cmdv;
	int		status;

	cmdv = make_cmdv(rc);
	pid = fork();
	if (pid == -1)
	{
		printf("fork error\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		make_pipe(cmd_i, pipe_cnt, pipe_fd);
		set_pipe_fd(pipe_cnt, cmd_i, pipe_fd);
		printf("%s\n", rc->cmd->cmd);
		// if (execve(rc->cmd->cmd, cmdv, NULL) == -1)
		// {
		// 	printf("exec error\n");
		// 	exit(EXIT_FAILURE);
		// }
		exit(0);
	}
	else
	{
		pid = wait(&status);
		if (pid == -1)
			printf("fork error\n");
	}
}

void	free_pipe_fd(int **pipe_fd, int pipe_cnt)
{
	int	i;

	i = 0;
	while (i < pipe_cnt)
	{
		printf("flag1\n");
		free(pipe_fd[i]);
		i++;
	}
	printf("flag\n");
	free(pipe_fd);
}

void	close_pipe(int cmd_i, int pipe_cnt, int **pipe_fd)
{
	if (cmd_i != pipe_cnt)
	{
		close(pipe_fd[cmd_i][0]);
		close(pipe_fd[cmd_i][1]);
	}
}

void	pipe_process(t_list *cmd, int pipe_cnt)
{
	int				cmd_i;
	int				**pipe_fd;
	t_list			*current_cmd;
	t_redirect_cmd	*rc;

	pipe_fd = malloc_pipe_fd(pipe_cnt);
	cmd_i = 0;
	current_cmd = cmd;
	while (cmd_i < pipe_cnt + 1)
	{
		rc = current_cmd->content;
		exec_cmd(rc, pipe_cnt, cmd_i, pipe_fd);
		// close_pipe(cmd_i, pipe_cnt, pipe_fd);
		cmd_i++;
		current_cmd = current_cmd->next;
	}
	free_pipe_fd(pipe_fd, pipe_cnt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:07:42 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/11 21:53:46 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

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

void	exec_cmd(t_cmd *rc, int pipe_cnt, int cmd_i, int **pipe_fd)
{
	int		pid;
	char	**cmdv;
	char	*cmd_path;

	cmdv = convert_arglst_to_array(rc);
	pid = fork();
	if (pid == -1)
	{
		printf("fork error\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		set_pipe_fd(pipe_cnt, cmd_i, pipe_fd);
		cmd_path = ft_strjoin("/bin/", cmdv[0]);
		if (execve(cmd_path, cmdv, NULL) == -1)
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

void	wait_process(int pipe_cnt)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipe_cnt + 1)
	{
		printf("%s %d\n", __FILE__, __LINE__);
		if (wait(&status) == -1)
		{
			printf("cprocess error\n");
			exit(EXIT_FAILURE);
		}
		printf("%s %d\n", __FILE__, __LINE__);
		i++;
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

void	pipe_process(t_list *cmd, int pipe_cnt)
{
	int		cmd_i;
	int		**pipe_fd;
	t_list	*current_cmd;
	t_cmd	*rc;

	pipe_fd = malloc_pipe_fd(pipe_cnt);
	cmd_i = 0;
	current_cmd = cmd;
	while (cmd_i < pipe_cnt + 1)
	{
		rc = (t_cmd *)current_cmd->content;
		make_pipe(cmd_i, pipe_cnt, pipe_fd);
		exec_cmd(rc, pipe_cnt, cmd_i, pipe_fd);
		close_pipe(pipe_fd, cmd_i);
		cmd_i++;
		current_cmd = current_cmd->next;
	}
	wait_process(pipe_cnt);
	free_pipe_fd(pipe_fd, pipe_cnt);
	printf("%s %d\n", __FILE__, __LINE__);
}

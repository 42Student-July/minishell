#include "command.h"
#include "errno.h"

void	malloc_pipe_fd(t_pipe_attr *pa)
{
	int	i;

	pa->pipe_fd = (int **)malloc(sizeof(int *) * pa->pipe_count);
	if (pa->pipe_fd == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pa->pipe_count)
	{
		pa->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pa->pipe_fd[i] == NULL)
		{
			printf("malloc error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return ;
}

void	malloc_cpid_array(t_pipe_attr *pa)
{
	pa->cpid_array = (int *)malloc(sizeof(int *) * (pa->pipe_count + 1));
	if (pa->cpid_array == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
}

void	make_pipe(t_pipe_attr *pa)
{
	if (pa->cmd_i != pa->pipe_count)
	{
		pipe(pa->pipe_fd[pa->cmd_i]);
	}
}

void	set_pipe_fd(t_pipe_attr *pa)
{
	if (pa->cmd_i == 0)
	{
		dup2(pa->pipe_fd[pa->cmd_i][PIPE_OUT], STDOUT_FILENO);
		close(pa->pipe_fd[pa->cmd_i][PIPE_IN]);
		close(pa->pipe_fd[pa->cmd_i][PIPE_OUT]);
	}
	else if (pa->cmd_i == pa->pipe_count)
	{
		dup2(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN], STDIN_FILENO);
		close(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN]);
		close(pa->pipe_fd[pa->cmd_i - 1][PIPE_OUT]);
	}
	else
	{
		dup2(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN], STDIN_FILENO);
		dup2(pa->pipe_fd[pa->cmd_i][PIPE_OUT], STDOUT_FILENO);
		close(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN]);
		close(pa->pipe_fd[pa->cmd_i - 1][PIPE_OUT]);
		close(pa->pipe_fd[pa->cmd_i][PIPE_IN]);
		close(pa->pipe_fd[pa->cmd_i][PIPE_OUT]);
	}
}

void	close_pipe(t_pipe_attr *pa)
{
	close(pa->pipe_fd[pa->cmd_i - 1][PIPE_IN]);
	close(pa->pipe_fd[pa->cmd_i - 1][PIPE_OUT]);
}

void	wait_process(t_pipe_attr *pa)
{
	int		status;
	int		i;
	pid_t	pid;
	bool	is_EINTR;

	i = 0;
	while (i < pa->pipe_count + 1)
	{
		is_EINTR = false;
		while (true)
		{
			pid = waitpid(pa->cpid_array[i], &status, 0);
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
void	exec_cmd(t_exec_attr *ea, t_pipe_attr *pa)
{
	int		pid;
	char	**cmdv;
	char	*cmd_path;
	char	**environ;

	cmd_path = NULL;
	cmdv = convert_lst_to_argv(pa->current_cmd->args);
	environ = convert_envlst_to_array(ea);
	pid = fork();
	pa->cpid_array[pa->cmd_i] = pid;
	if (pid == -1)
	{
		printf("fork error\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (has_redirect_file(pa->current_cmd))
			open_files_in_pipe(pa->current_cmd, ea);
		set_pipe_fd(pa);
		if (!is_self_cmd(pa->current_cmd->cmd))
		{
			if (is_path(pa->current_cmd->cmd))
			{
				cmd_path = ft_strdup(pa->current_cmd->cmd);
				if (cmd_path == NULL)
				{
					printf("ft_strdup error\n");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				cmd_path = find_path(pa->current_cmd->cmd, ea, pa->cmd_i);
				if (cmd_path == NULL)
				{
					if (ea->has_not_permission[pa->cmd_i])
					{
						ft_put_cmd_error(pa->current_cmd->cmd, "Permission denied");
						exit(126);
					}
					else
					{
						ft_put_cmd_error(pa->current_cmd->cmd, "command not found");
						g_exit_status = 127;
						exit(127);
					}
				}
			}
			// cmd_pathがディレクトリか確認する処理
			if (is_dir(cmd_path))
			{
				ft_put_cmd_error(pa->current_cmd->cmd, "is a directory");
				exit(126);
			}
		}
		if (has_redirect_file(pa->current_cmd))
			redirect(pa->current_cmd, ea);
		if (is_self_cmd(pa->current_cmd->cmd))
			execute_self_cmd(pa->current_cmd, ea, PIPE);
		else
		{
			if (execve(cmd_path, cmdv, environ) == -1)
			{
				execve_error(errno, pa->current_cmd->cmd);
				exit(EXIT_FAILURE);
			}
		}
		free(cmd_path);
		exit(0);
	}
	else if (pa->cmd_i > 0)
	{
		close_pipe(pa);
	}
	free_char_dptr(environ);
}

void	pipe_process(t_exec_attr *ea, int pipe_count)
{
	t_pipe_attr	pa;
	t_list		*tmp;

	pa.pipe_count = pipe_count;
	malloc_pipe_fd(&pa);
	malloc_cpid_array(&pa);
	ea->has_not_permission = malloc_has_not_permission(pa.pipe_count + 1);
	pa.cmd_i = 0;
	tmp = ea->cmd_lst;
	while (pa.cmd_i < pa.pipe_count + 1)
	{
		pa.current_cmd = tmp->content;
		make_pipe(&pa);
		exec_cmd(ea, &pa);
		pa.cmd_i++;
		tmp = tmp->next;
	}
	wait_process(&pa);
	free_pipe_attr(&pa);
}

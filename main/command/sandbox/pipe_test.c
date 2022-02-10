#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "../lib/libft/libft.h"

static int	get_pipe_cnt(char **command_lst)
{
	int	i;
	int	pipe_cnt;

	i = 0;
	pipe_cnt = 0;
	while (command_lst[i] != NULL)
	{
		if (ft_strncmp(command_lst[i], "|", 1) == 0)
			pipe_cnt++;
		i++;
	}
	return (pipe_cnt);
}

static void	read_command_lst(char **command_lst, int *pipe_locate)
{
	int	i;
	int	pipe_cnt;

	i = 0;
	pipe_cnt = 0;
	while (command_lst[i] != NULL)
	{
		if (ft_strncmp(command_lst[i], "|", 1) == 0)
		{
			pipe_cnt++;
			pipe_locate[pipe_cnt] = i;
			command_lst[i] = NULL;
		}
		i++;
	}
}

static int	**malloc_pfd(int pipe_cnt)
{
	int	i;
	int	**pfd;

	pfd = (int **)malloc(sizeof(int) * pipe_cnt);
	if (pfd == NULL)
	{
		// malloc error
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pipe_cnt)
	{
		pfd[i] = (int *)malloc(sizeof(int) * 2);
		if (pfd[i] == NULL)
		{
			// malloc error
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pfd);
}

void	wait_pipe(int pipe_cnt)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipe_cnt + 1)
	{
		wait(&status);
		i++;
	}
}

void	set_pfd(int pipe_cnt, int command_i, int **pfd)
{
	if (command_i == 0)
	{
		dup2(pfd[command_i][1], 1);
		close(pfd[command_i][1]);
		close(pfd[command_i][0]);
	}
	else if (command_i == pipe_cnt)
	{
		dup2(pfd[command_i - 1][0], 0);
		close(pfd[command_i - 1][0]);
		close(pfd[command_i - 1][1]);
	}
	else
	{
		dup2(pfd[command_i - 1][0], 0);
		dup2(pfd[command_i][1], 1);
		close(pfd[command_i - 1][0]);
		close(pfd[command_i - 1][1]);
		close(pfd[command_i][0]);
		close(pfd[command_i][1]);
	}
}

void	free_pfd(int **pfd, int pipe_cnt)
{
	int i;

	i = 0;
	while(i < pipe_cnt)
	{
		free(pfd[i]);
		i++;
	}
	free(pfd);
}

void	loop_pipe_process(char **command_lst, int *pipe_locate, int pipe_cnt)
{
	int	command_i;
	int	**pfd;
	int	pid;

	pfd = malloc_pfd(pipe_cnt);
	command_i = 0;
	while (command_i < pipe_cnt + 1)
	{
		if (command_i != pipe_cnt)
			pipe(pfd[command_i]);
		pid = fork();
		if (pid == -1)
		{
			// エラー
			printf("fork error\n");
		}
		else if (pid == 0)
		{
			// 子プロセス
			set_pfd(pipe_cnt, command_i, pfd);
			// ここに今までの処理を書く
			execvp(command_lst[pipe_locate[command_i] + 1], \
					command_lst + pipe_locate[command_i] + 1);
			exit(0);
		}
		if (command_i != pipe_cnt)
		{
			// 親プロセス
			close(pfd[command_i][0]);
			close(pfd[command_i][1]);
		}
		command_i++;
	}
	free_pfd(pfd, pipe_cnt);
}

void	no_pipe_process()
{
	printf("pipe = 0\n");
}

void	pipe_process(char **command_lst, int pipe_cnt)
{
	int	*pipe_locate;

	pipe_locate = (int *)malloc(sizeof(int) * pipe_cnt + 1);
	if (pipe_locate == NULL)
	{
		// malloc error
		exit(EXIT_FAILURE);
	}
	pipe_locate[0] = -1;
	read_command_lst(command_lst, pipe_locate);
	loop_pipe_process(command_lst, pipe_locate , pipe_cnt);
	wait_pipe(pipe_cnt);
	free(pipe_locate);
}

int main()
{
	char *command_lst[] = {"ls", "|", "wc", "-l", NULL};
	int	pipe_cnt;

	pipe_cnt = get_pipe_cnt(command_lst);
	if (pipe_cnt == 0)
	{
		// パイプがないケース
		no_pipe_process();
	}
	else
	{
		// パイプがあるケース
		pipe_process(command_lst, pipe_cnt);
	}
	// free
	return 0;
}

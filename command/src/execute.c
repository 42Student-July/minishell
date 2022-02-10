/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 17:38:22 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	do_execute_cmd(t_redirect_cmd *rc)
{
	pid_t	pid;
	int		status;
	char	**cmdv;

	cmdv = make_cmdv()
	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		if (execve("/bin/", cmdv, NULL))
		{

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

void	no_pipe_process(t_list *cmd)
{
	t_redirect_cmd	*rc;

	rc = cmd->content;
	do_execute_cmd(rc);
}

void	pipe_process()
{

}

int	execute_cmd(t_list *cmd)
{
	int	pipe_cnt;

	pipe_cnt = ft_lstsize(cmd) - 1;
	if (pipe_cnt == 0)
	{
		no_pipe_process(cmd);
	}
	else
	{
		pipe_process(cmd);
	}
	return (0);
}

// int	execute_cmd(t_list *cmd)
// {
// 	t_exec_attr	*e_attr;

// 	(void)cmd;
// 	int argc = 0;
// 	const char **argv = NULL;
// 	init(&e_attr);
// 	create_cmd_from_arg(argc, argv, e_attr);
// 	if (is_self_cmd(argv[1]))
// 		execute_self(e_attr);
// 	else
// 		execute_builtin(e_attr);
// 	return (0);
// }

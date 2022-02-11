/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/11 14:01:59 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	print_cmdv(char **cmdv)
{
	int i = 0;

	printf("start print_cmdv\n");
	while (cmdv[i] != NULL)
	{
		printf("%s\n", cmdv[i]);
		i++;
	}
}

void	do_execute_cmd(t_redirect_cmd *rc)
{
	pid_t	pid;
	int		status;
	char	**cmdv;

	cmdv = convert_arglst_to_array(rc);
	// print_cmdv(cmdv);
	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		if (execve(rc->cmd->cmd, cmdv, NULL) == -1)
		{
			printf("exec error\n");
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

int	execute_cmd(t_list *cmd)
{
	int	pipe_cnt;

	printf("%sstart execute_cmd\n%s", F_BLUE, F_RESET);
	pipe_cnt = ft_lstsize(cmd) - 1;
	if (pipe_cnt == 0)
	{
		no_pipe_process(cmd);
	}
	else
	{
		pipe_process(cmd, pipe_cnt);
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

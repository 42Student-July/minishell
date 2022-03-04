/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:33 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/04 01:55:01 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"
#include "common.h"

static bool	is_num(char *str)
{
	size_t	i;

	if (!(str[0] == '+' || str[0] == '-' || ft_isdigit(str[0])))
		return (false);
	if ((str[0] == '+' || str[0] == '-') && ft_strlen(str) == 1)
		return (false);
	i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static char	*get_arg1(t_cmd *cmd)
{
	char	*arg1;
	t_list	*arg1_lst;

	arg1_lst = cmd->args->next;
	if (arg1_lst == NULL)
		return (cmd->args->content);
	arg1 = arg1_lst->content;
	return (ft_strtrim(arg1, " "));
}

int	exec_self_exit(t_cmd *cmd, t_exec_attr *ea, bool is_pipe)
{
	unsigned int	exit_status;
	int				argc;
	char			*arg1;
	long			arg1_num;

	(void)ea;
	if (!is_pipe) // pipeのときは出力しないらしい
		ft_putendl_fd("exit", STDERR_FILENO);
	argc = ft_lstsize(cmd->args);
	if (argc == 1)
		exit(g_exit_status);
	arg1 = get_arg1(cmd);
	if (arg1 == NULL)
		exit(EXIT_FAILURE);
	if (!is_num(arg1) || !ft_atol(arg1, &arg1_num))
	{
		ft_put_arg_error("exit", arg1, "numeric argument required");
		exit(255);
	}
	free(arg1);
	if (argc > 2)
	{
		ft_put_cmd_error("exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	exit_status = arg1_num;
	if (exit_status > 255)
		exit(exit_status % 256);
	else
		exit(exit_status);
	return (exit_status); // 無いとエラーになるので飾り
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_attribute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:31:09 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/16 09:52:12 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_cmd	*get_cmd(t_exec_attr *ea)
{
	return ((t_cmd *)ea->cmd_lst->content);
}

// コマンド名をgetする
char	*get_cmd_name(t_list *cmd_lst)
{
	t_cmd	*cmd;

	cmd = cmd_lst->content;
	return (cmd->cmd);
}

char	**get_args(t_list *cmd_lst, t_exec_attr *ea)
{
	t_cmd	*cmd;
	char	**args;

	cmd = cmd_lst->content;
	args = convert_lst_to_argv(cmd->args);
	if (args == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	return (args);
}

char	*get_cmd_arg(t_list *cmd_lst, t_exec_attr *ea)
{
	char	**args;

	args = get_args(cmd_lst, ea);
	return (args[CMD_ARG]);
}

char	**get_args_new(t_cmd *cmd, t_exec_attr *ea)
{
	char	**args;

	args = convert_lst_to_argv(cmd->args);
	if (args == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	return (args);
}

char	*get_cmd_args(t_cmd *cmd, t_exec_attr *ea)
{
	char	**args;

	args = get_args_new(cmd, ea);
	return (args[CMD_ARG]);
}

char	*get_argv_one(t_cmd *cmd)
{
	if (cmd->args == NULL)
	{
		ft_putstr_fd("no command", STDERR_FILENO);
		return (NULL);
	}
	if (cmd->args->next == NULL)
	{
		ft_putstr_fd("no args", STDERR_FILENO);
		return (NULL);
	}
	return (cmd->args->next->content);
}

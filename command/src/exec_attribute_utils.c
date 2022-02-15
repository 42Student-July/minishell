/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_attribute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:31:09 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/15 14:04:18 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_exec_cmd	*get_exec_cmd(t_exec_attr *ea)
{
	t_redirect_cmd	*rc;

	rc = ea->cmd_lst->content;
	return (rc->cmd);
}

// コマンド名をgetする
char	*get_cmd_name(t_list *cmd)
{
	t_redirect_cmd	*rc;

	rc = cmd->content;
	return (rc->cmd->cmd);
}

char	**get_args(t_list *cmd, t_exec_attr *ea)
{
	t_redirect_cmd	*rc;
	char			**args;

	rc = cmd->content;
	args = convert_lst_to_argv(rc->cmd->args);
	if (args == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	return (args);
}

char	*get_cmd_arg(t_list *cmd, t_exec_attr *ea)
{
	char	**args;

	args = get_args(cmd, ea);
	return (args[CMD_ARG]);
}

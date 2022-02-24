/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:07:21 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/24 16:01:37 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

bool	is_redirect_flag(t_exec_attr *ea)
{
	(void)ea;
	// if (cmd->filename_in != NULL || cmd->filename_out != NULL)
	// 	return (true);
	return (false);
}

bool	has_redirect_file(t_cmd *cmd)
{
	if (cmd->filenames_in != NULL || cmd->filenames_out != NULL)
		return (true);
	return (false);
}

void	redirect_dev_null(t_exec_attr *ea)
{
	ea->stdout_copy = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	if (open("/dev/null", O_WRONLY) == -1)
		abort_minishell(OPEN_ERROR, ea);
}

void	redirect_in(t_cmd *cmd, t_exec_attr *ea)
{
	ea->stdin_copy = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	if (open(get_filename(cmd, IN), O_RDONLY) == -1)
		abort_minishell(OPEN_ERROR, ea);
}

void	redirect_out(t_cmd *cmd, t_exec_attr *ea)
{
	ea->stdout_copy = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	if (open(get_filename(cmd, OUT), O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1)
		abort_minishell(OPEN_ERROR, ea);
}

void	redirect(t_cmd *cmd, t_exec_attr *ea)
{
	if (cmd->filenames_in != NULL)
		redirect_in(cmd, ea);
	if (cmd->filenames_out != NULL)
		redirect_out(cmd, ea);
}

void	revert_redirect_in(t_exec_attr *ea)
{
	close(STDIN_FILENO);
	if (dup2(ea->stdin_copy, STDIN_FILENO) == -1)
		abort_minishell(OPEN_ERROR, ea);
}

void	revert_redirect_out(t_exec_attr *ea)
{
	close(STDOUT_FILENO);
	if (dup2(ea->stdout_copy, STDOUT_FILENO) == -1)
		abort_minishell(OPEN_ERROR, ea);
}


void	revert_direction(t_cmd *cmd, t_exec_attr *ea)
{
	if (cmd->filenames_in != NULL)
		revert_redirect_in(ea);
	if (cmd->filenames_out != NULL)
		revert_redirect_out(ea);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:07:21 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/03 17:17:49 by mhirabay         ###   ########.fr       */
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

// void	redirect_dev_null(t_exec_attr *ea)
// {
// 	ea->stdout_copy = dup(STDOUT_FILENO);
// 	close(STDOUT_FILENO);
// 	if (open("/dev/null", O_WRONLY) == -1)
// 		abort_minishell(OPEN_ERROR, ea);
// }

void	redirect_dev_null(t_exec_attr *ea)
{
	int	fd;

	(void)ea;
	fd = open("/dev/null", O_WRONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	change_fd(t_list *files)
{
	t_file	*f;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = files;
	while (tmp != NULL)
	{
		f = (t_file *)tmp->content;
		dup2(f->fd, STDOUT_FILENO);
		close(f->fd);
		tmp = tmp->next;
		i++;
	}
}

void	redirect(t_cmd *cmd, t_exec_attr *ea)
{
	(void)ea;
	if (cmd->filenames_in != NULL)
		change_fd(cmd->filenames_in);
	if (cmd->filenames_out != NULL)
		change_fd(cmd->filenames_out);
}

void	reset_stdfd(t_exec_attr *ea)
{
	dup2(ea->stdfd[0], STDIN_FILENO);
	dup2(ea->stdfd[1], STDOUT_FILENO);
	dup2(ea->stdfd[2], STDERR_FILENO);
}

bool	open_files_out(t_cmd *cmd, t_exec_attr *ea)
{
	t_list	*current_filename;
	t_file	*f;
	int		i;
	int		fd;

	(void)ea;
	current_filename = cmd->filenames_out;
	i = 0;
	while (current_filename != NULL)
	{
		f = (t_file *)current_filename->content;
		// アペンドのリダイレクト
		if (f->is_double)
			fd = open(f->filename, \
						O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open(f->filename, \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			perror(f->filename);
			g_exit_status = EXIT_FAILURE;
			return (false);
		}
		f->fd = fd;
		current_filename = current_filename->next;
		i++;
	}
	return (true);
}

bool	open_files_in(t_cmd *cmd, t_exec_attr *ea)
{
	t_list	*current_filename;
	t_file	*f;
	int		i;
	int		fd;

	(void)ea;
	current_filename = cmd->filenames_in;
	i = 0;
	while (current_filename != NULL)
	{
		f = (t_file *)current_filename->content;
		fd = open(f->filename, O_RDONLY);
		if (fd == -1)
		{
			perror(f->filename);
			g_exit_status = EXIT_FAILURE;
			return (false);
		}
		f->fd = fd;
	}
	return (true);
}

bool	open_files(t_cmd *cmd, t_exec_attr *ea)
{
	if (!open_files_in(cmd, ea))
		return (false);
	if (!open_files_out(cmd, ea))
		return (false);
	return (true);
}

bool	open_files_in_pipe(t_cmd *cmd, t_exec_attr *ea)
{
	if (!open_files_in(cmd, ea))
		exit(EXIT_FAILURE);
	if (!open_files_out(cmd, ea))
		exit(EXIT_FAILURE);
	return (true);
}

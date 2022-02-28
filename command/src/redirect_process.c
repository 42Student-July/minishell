/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:07:21 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/28 15:32:23 by tkirihar         ###   ########.fr       */
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

void	redirect_in(t_cmd *cmd, t_exec_attr *ea)
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
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		current_filename = current_filename->next;
		i++;
	}
}

void	redirect_out(t_cmd *cmd, t_exec_attr *ea)
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
		if (f->is_double) // アペンドのリダイレクト
		{
			fd = open(f->filename, \
						O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else // デフォルトのリダイレクト
		{
			fd = open(f->filename, \
						O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		current_filename = current_filename->next;
		i++;
	}
}

void	redirect(t_cmd *cmd, t_exec_attr *ea)
{
	if (cmd->filenames_in != NULL)
		redirect_in(cmd, ea);
	if (cmd->filenames_out != NULL)
		redirect_out(cmd, ea);
}

void	reset_stdfd(t_exec_attr *ea)
{
	dup2(ea->stdfd[0], STDIN_FILENO);
	dup2(ea->stdfd[1], STDOUT_FILENO);
	dup2(ea->stdfd[2], STDERR_FILENO);
}


#include "../includes/command.h"


bool	has_redirect_file(t_cmd *cmd)
{
	if (cmd->filenames_in != NULL || cmd->filenames_out != NULL)
		return (true);
	return (false);
}

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

void	change_fd(t_list *files, bool is_in)
{
	t_file	*f;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = files;
	while (tmp != NULL)
	{
		f = (t_file *)tmp->content;
		if (is_in)
			dup2(f->fd, STDIN_FILENO);
		else
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
		change_fd(cmd->filenames_in, true);
	if (cmd->filenames_out != NULL)
		change_fd(cmd->filenames_out, false);
}

void	reset_stdfd(t_exec_attr *ea)
{
	dup2(ea->stdfd[0], STDIN_FILENO);
	dup2(ea->stdfd[1], STDOUT_FILENO);
	dup2(ea->stdfd[2], STDERR_FILENO);
}

bool	open_files_out(t_cmd *cmd)
{
	t_list	*current_filename;
	t_file	*f;
	int		fd;

	current_filename = cmd->filenames_out;
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
	}
	return (true);
}

bool	open_files_in(t_cmd *cmd)
{
	t_list	*current_filename;
	t_file	*f;
	int		fd;

	current_filename = cmd->filenames_in;
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
		current_filename = current_filename->next;
	}
	return (true);
}

bool	open_files(t_cmd *cmd, t_exec_attr *ea)
{
	(void)ea;
	if (!open_files_in(cmd))
		return (false);
	if (!open_files_out(cmd))
		return (false);
	return (true);
}

bool	open_files_in_pipe(t_cmd *cmd, t_exec_attr *ea)
{
	(void)ea;
	if (!open_files_in(cmd))
		exit(EXIT_FAILURE);
	if (!open_files_out(cmd))
		exit(EXIT_FAILURE);
	return (true);
}


#include "command.h"

bool	is_path(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

// 多分不要になる
// char	*find_execfile_in_currentdir(char *cmd, t_exec_attr *ea)
// {
// 	DIR				*dirp;
// 	struct dirent	*dp;
// 	char			*cmd_path;

// 	dirp = opendir(ea->current_pwd);
// 	if (dirp == NULL)
// 		return (NULL);
// 	dp = readdir(dirp);
// 	while (dp != NULL)
// 	{
// 		if (is_same_str(dp->d_name, cmd))
// 		{
// 			cmd_path = concat_path_and_cmd(ea->current_pwd, cmd);
// 			if (cmd_path == NULL)
// 				exit(EXIT_FAILURE);
// 			return (cmd_path);
// 		}
// 		dp = readdir(dirp);
// 	}
// 	return (NULL);
// }

void	execute_ext_cmd(t_cmd *c, t_exec_attr *ea)
{
	pid_t	cpid;
	pid_t	wait_ret;
	int		status;
	char	**cmdv;
	char	*cmd_path;
	char	**environ;

	cmdv = convert_lst_to_argv(c->args);
	if (is_path(c->cmd))
	{
		cmd_path = ft_strdup(c->cmd);
		if (cmd_path == NULL)
		{
			printf("ft_strdup error\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd_path = find_path(c->cmd, ea, 0);
		if (cmd_path == NULL)
		{
			free_char_dptr(cmdv);
			if (ea->has_not_permission[0])
			{
				ft_put_cmd_error(c->cmd, "Permission denied");
				g_exit_status = 126;
				return ;
			}
			else
			{
				ft_put_cmd_error(c->cmd, "command not found");
				g_exit_status = 127;
				return ;
			}
		}
	}
	environ = convert_envlst_to_array(ea);
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cpid == 0)
	{
		if (is_dir(cmd_path))
		{
			ft_put_cmd_error(c->cmd, "is a directory");
			exit(126);
		}
		if (has_redirect_file(c))
			redirect(c, ea);
		if (execve(cmd_path, cmdv, environ) == -1)
		{
			execve_error(errno, c->cmd);
		}
		free(cmd_path);
		free_char_dptr(cmdv);
		free_char_dptr(environ);
	}
	else
	{
		free(cmd_path);
		free_char_dptr(cmdv);
		free_char_dptr(environ);
		while (true)
		{
			wait_ret = waitpid(cpid, &status, 0);
			if (wait_ret > 0)
				break ;
			if (WIFSIGNALED(status))
				continue ;
			exit(EXIT_FAILURE);
		}
		if (!WIFSIGNALED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

void	no_pipe_process(t_exec_attr *ea)
{
	t_cmd *c;

	c = get_cmd(ea);
	ea->has_not_permission = malloc_has_not_permission(1);
	// fileのopenの処理はコマンドに関わらず行う
	if (has_redirect_file(c))
		if (!open_files(c, ea))
		{
			free(ea->has_not_permission);
			return ;
		}
			
	// TODO: コマンドが存在しない時、ここでsegvする
	if (c->cmd == NULL)
	{
		free(ea->has_not_permission);
		return ;
	}
	if (is_self_cmd(c->cmd))
	{
		if (has_redirect_file(c))
			redirect(c, ea);
		execute_self_cmd(c, ea, NO_PIPE);
		if (has_redirect_file(c))
			reset_stdfd(ea);
	}
	else
		execute_ext_cmd(c, ea);
	free(ea->has_not_permission);
}

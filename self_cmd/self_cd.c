/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:54 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/21 13:50:41 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	update_all_environ(char *pwd, t_exec_attr *ea)
{
	char	*export_pwd;
	char	*export_oldpwd;
	char	*old_pwd;

	// OLDPWDは前のPWDからパクって来る
	old_pwd = ft_kvsget_value(get_lst_by_key(ea->env_lst, "PWD")->content);
	export_oldpwd = ft_kvsget_value \
		(get_lst_by_key(ea->export_lst, "PWD")->content);
	update_value(ea->env_lst, "OLDPWD", old_pwd, ea);
	update_value(ea->env_lst, "PWD", pwd, ea);
	export_pwd = create_export_value(pwd);
	if (export_pwd == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	update_value(ea->export_lst, "OLDPWD", export_oldpwd, ea);
	update_value(ea->export_lst, "PWD", pwd, ea);
}

char	*create_new_pwd(char *oldpwd, char *path)
{
	char	*new_value;
	size_t	new_value_len;
	size_t	path_len;
	size_t	oldpwd_len;

	oldpwd_len = ft_strlen(oldpwd);
	path_len = ft_strlen(path);
	new_value_len = (oldpwd_len + SLASH + path_len + NULL_CHAR);
	new_value = (char *)ft_calloc(sizeof(char), new_value_len);
	if (new_value == NULL)
		return (NULL);
	ft_strlcat(new_value, oldpwd, new_value_len);
	ft_strlcat(new_value, "/", new_value_len);
	ft_strlcat(new_value, path, new_value_len);
	return (new_value);
}

bool	is_symlink(char *path, t_exec_attr *ea)
{
	struct stat	buf;
	char		*old_pwd;
	char		*pwd;

	old_pwd = ft_kvsget_value(get_lst_by_key(ea->env_lst, "PWD")->content);
	pwd = create_new_pwd(old_pwd, path);
	lstat(pwd, &buf);
	free(pwd);
	return (S_ISLNK(buf.st_mode));
}

bool	is_end_of_slash(char *path)
{
	size_t	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	if (path[i - 1] == '/')
		return (true);
	return (false);
}

char	*create_str_removed_end(char *path)
{
	size_t	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	path[i - 1] = '\0';
	return (ft_strdup(path));
}


int	x_chdir(char *arg, t_exec_attr *ea)
{
	char	*pwd;
	char	*old_pwd;
	char	*path;

	if (is_end_of_slash(arg))
	{
		path = create_str_removed_end(arg);
		if (path == NULL)
			abort_minishell(MALLOC_ERROR, ea);
	}
	else
		path = arg;
	if (chdir(path) == -1)
	{		
		print_error(CD, path);
		return (1);
	}
	if (is_symlink(path, ea))
	{
		
	}
	// 大文字の入力だったときのPWDの対応
	if (has_caps(path))
	{
		old_pwd = ft_kvsget_value(get_lst_by_key(ea->env_lst, "PWD")->content);
		pwd = create_new_pwd(old_pwd, path);
		if (pwd == NULL)
			abort_minishell(MALLOC_ERROR, ea);
	}
	else
	{
		redirect_dev_null(ea);
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			revert_redirect_out(ea);
			print_error(PWD, path);
			return (1);
		}
		revert_redirect_out(ea);
	}
	update_all_environ(pwd, ea);
	if (is_end_of_slash(arg))
		free(path);
	return (0);
}

int	exec_self_cd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;

	argv_one = get_argv_one(cmd);
	if (argv_one == NULL)
		return (1);
	// TODO: 引数が２つある場合などにも対応する
	return (x_chdir(argv_one, ea));
}

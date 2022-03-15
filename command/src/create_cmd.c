/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:51:35 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/15 14:34:33 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

char	*concat_path_and_cmd(char *path, char *command)
{
	char			*new_cmd;
	size_t			new_cmd_len;

	new_cmd_len = ft_strlen(path) + SLASH + ft_strlen(command) + NULL_CHAR;
	new_cmd = (char *)ft_xcalloc(sizeof(char), (new_cmd_len));
	ft_strlcat(new_cmd, path, new_cmd_len);
	ft_strlcat(new_cmd, "/", new_cmd_len);
	ft_strlcat(new_cmd, command, new_cmd_len);
	return (new_cmd);
}

bool	is_invalid_permission(char *cmd_path, size_t cmd_i, t_exec_attr *ea)
{
	struct stat	stat_buf;
	bool		invalid_flag;

	invalid_flag = false;
	if (stat(cmd_path, &stat_buf) == -1)
		exit(EXIT_FAILURE);
	// 所有者の実行許可を確認している
	if ((stat_buf.st_mode & S_IXUSR) != S_IXUSR)
		invalid_flag = true;
	// 所有者の読み込み許可を確認している
	if ((stat_buf.st_mode & S_IRUSR) != S_IRUSR)
		invalid_flag = true;
	if (invalid_flag)
	{
		// 権限がなくてもエラーにはせず、PATHから他の実行ファイルが見つかるまでループを回す
		ea->has_not_permission[cmd_i] = true;
		free(cmd_path);
	}
	return (invalid_flag);
}

DIR	*xopendir(char *path)
{
	DIR		*dirp;

	dirp = opendir(path);
	if (dirp == NULL)
	{
		return (NULL);
	}
	return (dirp);
}

char	*ret_cmd(char *cmd, DIR *dirp)
{
	closedir(dirp);
	return (cmd);
}

char	*create_cmd_from_path(char *cmd, char **path, t_exec_attr *ea, size_t cmd_i)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*new_cmd;
	size_t			i;

	i = 0;
	while (path[i] != NULL)
	{
		dirp = xopendir(path[i]);
		if (dirp != NULL)
		{
			dp = readdir(dirp);
			while (dp != NULL)
			{
				if (is_same_str(dp->d_name, cmd))
				{
					new_cmd = concat_path_and_cmd(path[i], cmd);
					if (is_invalid_permission(new_cmd, cmd_i, ea))
						break ;
					closedir(dirp);
					return (cmd);
				}
				dp = readdir(dirp);
			}
			closedir(dirp);
		}
		i++;
	}
	return (NULL);
}

// カレントディレクトリを指す":"を"."に置換する処理
char	*replace_colon_to_currentdir(char *env_path)
{
	char	*ret;
	char	*tmp;

	if (env_path[0] == ':')
	{
		ret = ft_xstrjoin(".", env_path);
		if (ret == NULL)
			exit(EXIT_FAILURE);
		free(env_path);
		return (ret);
	}
	ret = ft_replace_str(env_path, "::", ":.:");
	if (ret == NULL)
		exit(EXIT_FAILURE);
	if (env_path[ft_strlen(env_path) - 1] == ':')
	{
		tmp = ft_xstrjoin(ret, ".");
		if (tmp == NULL)
			exit(EXIT_FAILURE);
		free(ret);
		ret = tmp;
	}
	return (ret);
}

// TODO: 引数を一つにする
char	*find_path(char *cmd_name, t_exec_attr *ea, size_t cmd_i)
{
	char			*env_path;
	char			**path;
	char			*new_cmd;
	t_list			*lst;

	lst = get_lst_by_key(ea->env_lst, "PATH");
	if (lst == NULL)
		return (NULL);
	env_path = ft_kvsget_value(lst->content);
	if (env_path == NULL)
		return (NULL);
	env_path = replace_colon_to_currentdir(env_path);
	path = ft_xsplit(env_path, ':');
	free(env_path);
	new_cmd = create_cmd_from_path(cmd_name, path, ea, cmd_i);
	free_char_dptr(path);
	if (new_cmd == NULL)
		return (NULL);
	return (new_cmd);
}

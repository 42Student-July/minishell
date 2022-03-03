/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:54 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/03 13:08:49 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	update_all_environ(char *new_pwd, t_exec_attr *ea)
{
	char	*export_new_pwd;
	char	*export_pwd;
	char	*pwd;
	t_list	*pwdlst;

	pwdlst = get_lst_by_key(ea->env_lst, "PWD");
	if (pwdlst == NULL)
		// unsetでPWDがなくなったケース
		pwd = ft_strdup("");
	else
	{
		// export PWD= PWDの値を空文字に上書きしたケース
		if (ft_strlen(ft_kvsget_value(pwdlst->content)) == 0)
			pwd = ft_strdup("");
		else
			pwd = ea->current_pwd;
	}
	ea->current_pwd = new_pwd;
	export_pwd = create_export_value(pwd);
	export_new_pwd = create_export_value(new_pwd);
	if (export_new_pwd == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	if (pwdlst != NULL)
	{
		update_value(ea->env_lst, "PWD", new_pwd, ea);
		update_value(ea->export_lst, "PWD", export_new_pwd, ea);
	}
	update_value(ea->env_lst, "OLDPWD", pwd, ea);
	update_value(ea->export_lst, "OLDPWD", export_pwd, ea);
}

char	*create_new_pwd(char *pwd, char *path)
{
	char	*new_value;
	size_t	new_value_len;
	size_t	path_len;
	size_t	pwd_len;

	pwd_len = ft_strlen(pwd);
	path_len = ft_strlen(path);
	// virtual pathの場合、最後に"/"が入る場合があるため、新しい"/"とかぶってしまう。
	// なので、/を余分に付け加えないようにする
	if (pwd[pwd_len - 1] == '/')
		new_value_len = (pwd_len + path_len + NULL_CHAR);
	else
		new_value_len = (pwd_len + SLASH + path_len + NULL_CHAR);
	new_value = (char *)ft_calloc(sizeof(char), new_value_len);
	if (new_value == NULL)
		return (NULL);
	ft_strlcat(new_value, pwd, new_value_len);
	if (pwd[pwd_len - 1] != '/')
		ft_strlcat(new_value, "/", new_value_len);
	ft_strlcat(new_value, path, new_value_len);
	return (new_value);
}

bool	is_symlink(char *path, t_exec_attr *ea)
{
	struct stat	buf;
	char		*pwd;
	char		*new_pwd;

	pwd = ea->current_pwd;
	new_pwd = create_new_pwd(pwd, path);
	lstat(new_pwd, &buf);
	free(new_pwd);
	return (S_ISLNK(buf.st_mode));
}

bool	is_end_of_slash(char *path)
{
	size_t	i;

	i = 0;
	// slash onlyの場合は対象外とする
	if (ft_strlen(path) == 1)
		return (false);
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

bool	is_current_dir_exist(t_exec_attr *ea)
{
	char	*pwd;

	(void)ea;
	redirect_dev_null(ea);
	pwd = getcwd(NULL, 0);
	reset_stdfd(ea);
	if (pwd == NULL)
		return (false);
	return (true);
}

void	create_virtual_path(char *path, t_exec_attr *ea)
{
	char	*pwd;
	char	*new_pwd;

	pwd = ea->current_pwd;
	redirect_dev_null(ea);
	new_pwd = getcwd(NULL, 0);
	reset_stdfd(ea);
	if (new_pwd == NULL)
	{
		new_pwd = create_new_pwd(pwd, path);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", STDERR_FILENO);
	}
	update_all_environ(new_pwd, ea);
}

char *remove_relative(char *path, t_exec_attr *ea)
{
	char	**split;
	char	**new_split;
	char	*new_str;
	size_t	i;
	size_t	new_str_len;
	size_t	ddot_count;
	size_t	dot_count;
	size_t	blank_count;
	size_t	new_split_len;

	i = 0;
	new_str_len = 0;
	ddot_count = 0;
	dot_count = 0;
	blank_count = 0;
	split = ft_split(path, '/');
	while (split[i] != NULL)
	{
		if (is_same_str("", split[i]))
		{
			blank_count++;
		}
		if (is_same_str(".", split[i]))
		{
			dot_count++;
		}
		if (is_same_str("..", split[i]))
		{
			ddot_count++;
		}
		i++;
	}
	new_split_len = i - blank_count - dot_count - (ddot_count * 2) + 1;
	new_split = (char **)malloc(sizeof(char *) * new_split_len);
	if (new_split == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	i = 0;
	size_t j = 0;
	while (split[i] != NULL)
	{	
		// もしパスに..が存在する場合、前のパスを削除する
		// ただし絶対パスの一番目を除く
		if (is_same_str("", split[i]))
		{
			i++;
			continue ;
		}
		if (is_same_str(".", split[i]))
		{
			i++;
			continue ;
		}
		if (is_same_str("..", split[i]))
		{
			// ddotがあったら一個前のnew_splitをfreeする
			// そのときjをデクリメントする
			// ただしjがマイナスになる場合はやめる
			if (j != 0)
			{
				free(new_split[j - 1]);
				new_split[j - 1] = NULL;
				j--;
			}
			i++;
			continue ;
		}
		new_split[j] = ft_strjoin("/", split[i]);
		new_str_len += ft_strlen(new_split[j]);
		j++;
		i++;
	}
	new_split[j] = NULL;
	// ..の数だけ後ろからpathを削除していく
	// もしnew_splitの値がすべて空文字 or ..だった場合、cdの向き先はhome(/)になる
	i = 0;
	if (new_split[0] == NULL)
	{
		new_str = ft_strdup("/");
		free_char_dptr(split);
		free_char_dptr(new_split);
		return (new_str);
	}
	new_str = (char *)calloc(sizeof(char), new_str_len + 1);
	if (new_str == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	i = 0;
	while (new_split[i] != NULL)
	{
		ft_strlcat(new_str, new_split[i], new_str_len + 1);
		i++;
	}
	if (is_end_of_slash(new_str))
	{
		path = create_str_removed_end(new_str);
		if (path == NULL)
			abort_minishell(MALLOC_ERROR, ea);
	}
	free_char_dptr(split);
	free_char_dptr(new_split);
	return (new_str);
}

bool	has_diff(char *path, t_exec_attr *ea)
{
	char		*cwd;
	char		*pwd;
	bool		flag;
	char		*pwd_del_dot;
	struct stat buf;

	redirect_dev_null(ea);
	cwd = getcwd(NULL, 0);
	reset_stdfd(ea);
	if (*path == '/')
		pwd = path;
	else
		pwd = create_new_pwd(ea->current_pwd, path);
	pwd_del_dot = remove_relative(pwd, ea);
	if (lstat(pwd_del_dot, &buf) == -1)
		return (false);
	flag = is_same_str(cwd, pwd_del_dot);
	if (*path != '/')
		free(pwd);
	free(pwd_del_dot);
	return (!flag);
}

int	x_chdir(char *arg, t_exec_attr *ea)
{
	char	*new_pwd;
	char	*path;
	char	*tmp;

	if (chdir(arg) == -1)
	{
		print_error(CD, arg);
		return (1);
	}
	if (!is_current_dir_exist(ea))
	{
		create_virtual_path(arg, ea);
		return (1);
	}
	if (is_end_of_slash(arg))
	{
		path = create_str_removed_end(arg);
		if (path == NULL)
			abort_minishell(MALLOC_ERROR, ea);
	}
	else
		path = arg;
	if (has_diff(path, ea))
	{
		tmp = create_new_pwd(ea->current_pwd, path);
		new_pwd = remove_relative(tmp, ea);
	}
	else
	{
		redirect_dev_null(ea);
		new_pwd = getcwd(NULL, 0);
		reset_stdfd(ea);
		if (new_pwd == NULL)
		{
			print_error(PWD, path);
			return (1);
		}
	}
	update_all_environ(new_pwd, ea);
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

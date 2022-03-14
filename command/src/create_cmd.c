
#include "../includes/command.h"

bool	is_dollar(char *arg)
{
	// TODO:あとでけす
	// readlineが無いので、引数に$を入れると元々の方の環境変数が呼ばれる。
	// quoteをつけても読めるように対応する
	// arg++;
	if (*arg == '$')
		return (true);
	return (false);
}

char	*convert_env_var(t_exec_attr *ea, char *arg)
{
	char	*key;
	t_list	*ret;
	char	*value;

	// $はkeyに不要なので一つポインタを進める
	// TODO:あとで消す quote対応
	arg = ft_strtrim(arg, "\'");
	key = ++arg;
	ret = get_lst_by_key(ea->env_lst, key);
	if (ret == NULL)
		return (NULL);
	value = ft_kvsget_value(ret->content);
	return (value);
}

char	*concat_path_and_cmd(char *path, char *command)
{
	char			*new_cmd;
	size_t			new_cmd_len;

	new_cmd_len = ft_strlen(path) + SLASH + ft_strlen(command) + NULL_CHAR;
	new_cmd = (char *)ft_calloc(sizeof(char), (new_cmd_len));
	if (new_cmd == NULL)
		return (NULL);
	ft_strlcat(new_cmd, path, new_cmd_len);
	ft_strlcat(new_cmd, "/", new_cmd_len);
	ft_strlcat(new_cmd, command, new_cmd_len);
	return (new_cmd);
}

bool	can_exec(char *cmd_path)
{
	struct stat	stat_buf;

	if (stat(cmd_path, &stat_buf) == -1)
		exit(EXIT_FAILURE);
	// 所有者の実行許可を確認している
	if ((stat_buf.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	// 所有者の読み込み許可を確認している
	if ((stat_buf.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

char	*create_cmd_from_path(char *cmd, char **path, t_exec_attr *ea, size_t cmd_i)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			i;
	char			*new_cmd;
	bool			is_break;

	i = 0;
	ea->has_not_permission[cmd_i] = false; // 初期化であって、権限があるわけではない
	while (path[i] != NULL)
	{
		is_break = false;
		dirp = opendir(path[i]);
		if (dirp == NULL)
		{
			i++;
			continue ;
		}
		dp = readdir(dirp);
		while (dp != NULL)
		{
			if (is_same_str(dp->d_name, cmd))
			{
				closedir(dirp);
				new_cmd = concat_path_and_cmd(path[i], cmd);
				if (new_cmd == NULL)
					abort_minishell_with(MALLOC_ERROR, ea, path);
				if (!can_exec(new_cmd))
				{
					// 権限がなくてもエラーにはせず、PATHから他の実行ファイルが見つかるまでループを回す
					ea->has_not_permission[cmd_i] = true;
					is_break = true;
					free(new_cmd);
					break ;
				}
				return (new_cmd);
			}
			dp = readdir(dirp);
		}
		i++;
		// breakで来た場合ここを通させない
		if (!is_break)
			closedir(dirp);
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
		ret = ft_strjoin(".", env_path);
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
		tmp = ft_strjoin(ret, ".");
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
	path = ft_split(env_path, ':');
	if (path == NULL)
		abort_minishell_with(MALLOC_ERROR, ea, path);
	new_cmd = create_cmd_from_path(cmd_name, path, ea, cmd_i);
	if (new_cmd == NULL)
	{
		free_char_dptr(path);
		free(env_path);
		return (NULL);
	}
	free_char_dptr(path);
	free(env_path);
	return (new_cmd);
}

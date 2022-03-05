/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:40:07 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/05 12:46:42 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// TODO: parserと統合するときに、修正不可避なのでテキトーな感じでok
void	create_cmd_from_arg(int argc, const char **argv, t_exec_attr *ea)
{
	(void)argc;
	(void)argv;
	(void)ea;
	// int		i;
	// char	**command;
	// char	*arg;
	// char	*bin_path;

	// i = 0;
	// bin_path = "/bin/";
	// if (is_self_cmd(argv[1]))
	// {
	// 	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	// 	if (command == NULL)
	// 		abort_minishell(MALLOC_ERROR, ea);
	// }
	// else
	// {
	// 	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	// 	if (command == NULL)
	// 		abort_minishell(MALLOC_ERROR, ea);
	// 	if (is_not_exec_path(argv[1]))
	// 	{
	// 		command[i] = ft_strjoin(bin_path, argv[1]);
	// 		if (command[i] == NULL)
	// 			abort_minishell(MALLOC_ERROR, ea);
	// 		i++;
	// 	}
	// }
	// while (i < argc - 1)
	// {
	// 	if (strcmp(argv[i + 1], "<") == 0)
	// 	{
	// 		ea->infile = strdup(argv[i + 2]);
	// 		i++;
	// 	}
	// 	else if (ft_strncmp(argv[i + 1], ">", ft_strlen(argv[i + 1])) == 0)
	// 	{
	// 		ea->outfile = strdup(argv[i + 2]);
	// 		i++;
	// 	}
	// 	else
	// 	{
	// 		arg = (char *)argv[i + 1];
	// 		if (is_dollar(arg))
	// 		{
	// 			arg = convert_env_var(ea, arg);
	// 			if (arg == NULL)
	// 			{
	// 				// $の後、環境変数に指定していない値が来た時、その引数の読み込みを飛ばす
	// 				// 検証をちゃんとしていないので、この辺は要検討
	// 				i++;
	// 				continue;
	// 			}
	// 		}
	// 		command[i] = ft_strdup(arg);
	// 		if (command[i] == NULL)
	// 			abort_minishell(MALLOC_ERROR, ea);
	// 		i++;
	// 	}
	// }
	// command[i] = NULL;
	// ea->command = command;
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

char	*create_cmd_from_path(char *cmd, char **path, t_exec_attr *ea)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			i;
	char			*new_cmd;

	i = 0;
	while (path[i] != NULL)
	{
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
				return (new_cmd);
			}
			dp = readdir(dirp);
		}
		i++;
		closedir(dirp);
	}
	return (NULL);
}

// TODO: 引数を一つにする
char	*find_path(char *cmd_name, t_exec_attr *ea)
{
	char			*env_path;
	char			**path;
	char			*new_cmd;
	t_list			*lst;

	lst = get_lst_by_key(ea->env_lst, "PATH");
	if (lst == NULL)
		return (NULL);
	env_path = ft_kvsget_value(lst->content);
	path = ft_split(env_path, ':');
	if (path == NULL)
		abort_minishell_with(MALLOC_ERROR, ea, path);
	new_cmd = create_cmd_from_path(cmd_name, path, ea);
	if (new_cmd == NULL)
		return (NULL);
	free_char_dptr(path);
	return (new_cmd);
}

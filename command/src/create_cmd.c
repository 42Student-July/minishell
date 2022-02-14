/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:40:07 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 09:59:45 by mhirabay         ###   ########.fr       */
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
	ret = get_list_by_key(ea->env_lst, key);
	if (ret == NULL)
		return (NULL);
	value = ft_kvsget_value(ret->content);
	return (value);
}

// TODO: parserと統合するときに、修正不可避なのでテキトーな感じでok
void	create_cmd_from_arg(int argc, const char **argv, t_exec_attr *ea)
{
	int		i;
	char	**command;
	char	*arg;
	char	*bin_path;

	i = 0;
	bin_path = "/bin/";
	if (is_self_cmd(argv[1]))
	{
		command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
		if (command == NULL)
			abort_minishell(MALLOC_ERROR, ea);
	}
	else
	{
		command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
		if (command == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		if (is_not_exec_path(argv[1]))
		{
			command[i] = ft_strjoin(bin_path, argv[1]);
			if (command[i] == NULL)
				abort_minishell(MALLOC_ERROR, ea);
			i++;
		}
	}
	while (i < argc - 1)
	{
		if (strcmp(argv[i + 1], "<") == 0)
		{
			ea->infile = strdup(argv[i + 2]);
			i++;
		}
		else if (ft_strncmp(argv[i + 1], ">", ft_strlen(argv[i + 1])) == 0)
		{
			ea->outfile = strdup(argv[i + 2]);
			i++;
		}
		else
		{
			arg = (char *)argv[i + 1];
			if (is_dollar(arg))
			{
				arg = convert_env_var(ea, arg);
				if (arg == NULL)
				{
					// $の後、環境変数に指定していない値が来た時、その引数の読み込みを飛ばす
					// 検証をちゃんとしていないので、この辺は要検討
					i++;
					continue;
				}
			}
			command[i] = ft_strdup(arg);
			if (command[i] == NULL)
				abort_minishell(MALLOC_ERROR, ea);
			i++;
		}
	}
	command[i] = NULL;
	ea->command = command;
}

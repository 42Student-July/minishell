/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:53:41 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/09 17:28:06 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

bool	is_sharp(char *arg)
{
	if (arg == NULL)
		return (false);
	// exportの第一引数が#から始まっている限り、なにが後ろにきたとしても、export(引数なし)と同じような実装になる。
	if (*arg == '#')
		return (true);
	return (false);
}

int	exec_self_export(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;
	bool	exit_stat;

	exit_stat = true;
	argv_one = get_argv_one(cmd);
	if (argv_one == NULL || is_sharp(argv_one))
		print_all_export_lst(ea);
	else
		export_with_args(cmd, ea, &exit_stat);
	if (exit_stat)
		return (0);
	return (1);
}

// 新しく追加
bool	addlst_sort_by_ascii(t_list **export_lst, char **arg)
{
	// まずadd_backでポインタの位置を確定した後、contentを入れ替える
	bool	flag;

	flag = ft_lstadd_back(export_lst, \
			ft_lstnew(ft_kvsnew(arg[KEY], \
				create_export_value(arg[VALUE]))));
	if (!flag)
		return (false);
	sort_listkey_by_ascii(*export_lst);
	return (true);
}

int	check_export_arg(char **arg)
{
	// ちょっと全部は把握しきれていないが、KEYに_以外の記号がはいったらout
	if (is_invalid_name(arg[KEY]))
		return (INVALID_IDENTIFER);
	if (arg[VALUE] == NULL)
		return (NO_VALUE);
	return (10);
}

void	export_with_args(t_cmd *cmd, t_exec_attr *ea, bool *exit_stat)
{
	char		**kv;
	int			ret;
	char		*arg;
	t_list		*lst;
	char		*tmp_str;

	lst = cmd->args->next;
	while (lst != NULL)
	{
		arg = (char *)(lst->content);
		// ft_splitでは引数が"a="の場合と"a"の判別がつけられない実装になっている
		// そのため、strchrでまず引数に=があるか判定してから、各実装に入る
		if (ft_strchr(arg, '=') == NULL)
		{
			if (is_invalid_name(arg))
			{
				print_error_msg_with_var(EXPORT, arg);
				lst = lst->next;
				*exit_stat = false;
				continue ;
			}
			store_arg_in_export(ea, arg, NULL);
			store_arg_in_env(ea, arg, NULL);
		}
		// 先頭ポインタが"="だったとき、keyが存在しないのでerrorとする
		else if (ft_strchr(arg, '=') == arg)
		{
			*exit_stat = false;
			print_error_msg_with_var(EXPORT, arg);
			lst = lst->next;
			continue ;
		}
		else
		{
			kv = ft_split(arg, '=');
			if (kv == NULL)
				abort_minishell(MALLOC_ERROR, ea);
			ret = check_export_arg(kv);
			if (ret == INVALID_IDENTIFER)
			{
				*exit_stat = false;
				print_error_msg_with_var(EXPORT, kv[KEY]);
			}
			else
			{
				if (ret == NO_VALUE)
				{
					// valueがnullだけど=が存在する場合、valueには\0を入れる。
					kv[VALUE] = ft_strdup("");
					if (kv[VALUE] == NULL)
						abort_minishell_with(MALLOC_ERROR, ea, kv);
				}
				tmp_str = ft_strtrim(kv[VALUE], " ");
				if (tmp_str == NULL)
					abort_minishell_with(MALLOC_ERROR, ea, kv);
				free(kv[VALUE]);
				kv[VALUE] = tmp_str;
				if (!store_arg_in_env(ea, kv[KEY], kv[VALUE]))
					abort_minishell_with(MALLOC_ERROR, ea, kv);
				if (!store_arg_in_export(ea, kv[KEY], kv[VALUE]))
					abort_minishell_with(MALLOC_ERROR, ea, kv);
			}
			free(kv);
		}
		lst = lst->next;
	}
}

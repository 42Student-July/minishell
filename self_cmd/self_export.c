/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:53:41 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 14:21:00 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

// 新しく追加
bool	addlst_sort_by_ascii(t_list **export_lst, char **arg)
{
	// まずadd_backでポインタの位置を確定した後、contentを入れ替える
	bool	flag;

	flag = ft_lstadd_back(export_lst, \
			ft_lstnew(create_kvs_content(arg[KEY], \
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

void	store_arg_only_export(t_exec_attr *ea, char *key)
{	
	if (!ft_lstadd_back(&ea->export_lst, \
			ft_lstnew(create_kvs_content(key, NULL))))
		abort_minishell(MALLOC_ERROR, ea);
	sort_listkey_by_ascii(ea->export_lst);
}

void	export_with_args(t_exec_attr *ea)
{
	char		**arg;
	bool		flag;
	int			ret;

	if (ea->command[CMD_ARG] != NULL)
	{
		// ft_splitでは引数が"a="の場合と"a"の判別がつけられない実装になっている
		// そのため、strchrでまず引数に=があるか判定してから、各実装に入る
		if (ft_strchr(ea->command[CMD_ARG], '=') == NULL)
			store_arg_only_export(ea, ea->command[CMD_ARG]);
		else
		{
			arg = ft_split(ea->command[CMD_ARG], '=');
			if (arg == NULL)
				abort_minishell(MALLOC_ERROR, ea);
			ret = check_export_arg(arg);
			if (ret == INVALID_IDENTIFER)
				print_error_msg_with_var(ea->command[CMD_ARG], arg[KEY]);
			else
			{
				if (ret == NO_VALUE)
				{
					// valueがnullだけど=が存在する場合、valueには\0を入れる。
					arg[VALUE] = ft_strdup("");
					if (arg[VALUE] == NULL)
						abort_minishell_with(MALLOC_ERROR, ea, arg);
				}
				flag = ft_lstadd_back(&ea->env_lst, \
				ft_lstnew(create_kvs_content(arg[KEY], arg[VALUE])));
				if (!flag)
					abort_minishell_with(MALLOC_ERROR, ea, arg);
				if (!addlst_sort_by_ascii(&ea->export_lst, arg))
					abort_minishell_with(MALLOC_ERROR, ea, arg);
			}
			free(arg);
		}
	}
}

void	exec_self_export(t_exec_attr *ea)
{
	if (ea->command[CMD_ARG] == NULL)
		print_all_export_lst(ea);
	else
		export_with_args(ea);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:53:41 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/15 09:32:43 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	exec_self_export(t_exec_attr *ea)
{
	(void)ea;
	if (get_cmd_arg(ea->cmd, ea) == NULL)
		print_all_export_lst(ea);
	else
		export_with_args(ea);
}

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

void	export_with_args(t_exec_attr *ea)
{
	char		**arg;
	int			ret;
	// ft_splitでは引数が"a="の場合と"a"の判別がつけられない実装になっている
	// そのため、strchrでまず引数に=があるか判定してから、各実装に入る
	if (ft_strchr(get_cmd_arg(ea->cmd, ea), '=') == NULL)
		store_arg_in_export(ea, get_cmd_arg(ea->cmd, ea), NULL);
	else
	{
		arg = ft_split(get_cmd_arg(ea->cmd, ea), '=');
		if (arg == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		ret = check_export_arg(arg);
		if (ret == INVALID_IDENTIFER)
			print_error_msg_with_var(get_cmd_arg(ea->cmd, ea), arg[KEY]);
		else
		{
			if (ret == NO_VALUE)
			{
				// valueがnullだけど=が存在する場合、valueには\0を入れる。
				arg[VALUE] = ft_strdup("");
				if (arg[VALUE] == NULL)
					abort_minishell_with(MALLOC_ERROR, ea, arg);
			}
			if (!store_arg_in_env(ea, arg[KEY], arg[VALUE]))
				abort_minishell_with(MALLOC_ERROR, ea, arg);
			if (!store_arg_in_export(ea, arg[KEY], arg[VALUE]))
				abort_minishell_with(MALLOC_ERROR, ea, arg);
		}
		free(arg);
	}
}

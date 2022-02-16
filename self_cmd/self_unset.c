/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:19:55 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/16 10:14:46 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	exec_self_unset(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;

	argv_one = get_argv_one(cmd);
	(void)ea;
	if (argv_one == NULL)
		return ;
	if (is_invalid_name(argv_one))
		print_error_msg_with_var(UNSET, argv_one);
	del_lst_by_key(ea->env_lst, argv_one);
	del_lst_by_key(ea->export_lst, argv_one);
}

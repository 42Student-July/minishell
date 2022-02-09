/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:26:06 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/09 14:35:08 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

bool	is_invalid_name(char *name)
{
	size_t	i;

	i = 0;
	// 数字は頭にあったら弾く
	if (ft_isdigit(name[i]))
		return (true);
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]))
			return (true);
		i++;
	}
	return (true);
}

void	print_error_msg_with_var(char *cmd_name, char *var)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(INVALID_IDENTIFER_MSG, STDERR_FILENO);
}

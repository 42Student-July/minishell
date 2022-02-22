/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:26:06 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/22 15:53:41 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

bool	is_invalid_name(char *name)
{
	size_t	i;

	i = 0;
	// 数字は頭にあったら弾く
	if (ft_isdigit(name[i]))
		return (true);
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) || name[i] == '_')
			return (true);
		i++;
	}
	return (false);
}

void	print_error_msg_with_var(char *cmd_name, char *var)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(INVALID_IDENTIFER_MSG, STDERR_FILENO);
}

void	print_error(char *cmd, char *input)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(input);
}

bool	has_caps(char *path)
{
	size_t	i;

	i = 0;
	while (path[i] != '\0')
	{
		if (ft_iscap_alpha(path[i]))
		{
			return (true);
		}
		i++;
	}
	return (false);
}

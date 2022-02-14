/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_attribute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:31:09 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/14 18:41:32 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_exec_cmd	*get_exec_cmd(t_exec_attr *ea)
{
	t_redirect_cmd	*rc;

	rc = ea->cmd->content;
	return (rc->cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:07:21 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 12:23:23 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

bool	is_redirect_flag(t_exec_attr *ea)
{
	if (ea->infile != NULL || ea->outfile != NULL)
		return (true);
	return (false);
}

void	change_direction(t_exec_attr *ea)
{
	if (ea->infile != NULL)
	{
		close(STDIN_FILENO);
		if (open(ea->infile, O_RDONLY) == -1)
			abort_minishell(ea->infile, ea);
	}
	if (ea->outfile != NULL)
	{
		close(STDOUT_FILENO);
		if (open(ea->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1)
			abort_minishell(ea->infile, ea);
	}
}

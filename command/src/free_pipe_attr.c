/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe_attr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:47:46 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/23 22:52:10 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	free_pipe_fd(t_pipe_attr *pa)
{
	int	i;

	i = 0;
	while (i < pa->pipe_count)
	{
		free(pa->pipe_fd[i]);
		i++;
	}
	free(pa->pipe_fd);
}

void	free_pipe_attr(t_pipe_attr *pa)
{
	// ここでpa->current_cmdもfreeすべきかも
	free_pipe_fd(pa);
	free(pa->cpid_array);
}

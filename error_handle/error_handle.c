/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:31:11 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 13:40:12 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handle.h"

void	free_exec_attr(t_exec_attr *ea)
{
	int	i;

	i = 0;

	if (ea->command != NULL)
	{
		while (ea->command[i] != NULL)
		{
			free(ea->command[i]);
			i++;
		}
		free((void *)ea->command);
	}
	if (ea != NULL)
		free(ea);
}

void	free_char_dptr(char **dptr)
{
	size_t	i;

	i = 0;
	if (dptr != NULL)
	{
		while (dptr[i] != NULL)
		{
			free(dptr[i]);
			i++;
		}
		free(dptr);
	}
}

void	abort_minishell(char *msg, t_exec_attr *ea)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (ea != NULL)
		free_exec_attr(ea);
	exit(EXIT_FAILURE);
}

void	abort_minishell_with(char *msg, t_exec_attr *ea, char **split)
{
	if (split != NULL)
		free_char_dptr(split);
	perror(msg);
	if (ea != NULL)
		free_exec_attr(ea);
	exit(EXIT_FAILURE);
}


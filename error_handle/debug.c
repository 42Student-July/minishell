/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:31:50 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/14 16:08:01 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handle.h"

void	print_command_debug(t_exec_attr *ea)
{
	size_t	i;

	i = 0;
	(void)ea;
	// while (ea->command[i] != NULL)
	// {
	// 	printf("ea->command[i] : %s\n", ea->command[i]);
	// 	i++;
	// }
}

void	print_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("line : %s\n", array[i]);
		i++;
	}
	printf("line_count = %zu\n", i + 1);
}

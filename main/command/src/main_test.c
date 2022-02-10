/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:57:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/09 14:54:14 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

int	main(int argc, const char *argv[])
{
	t_exec_attr	*e_attr;

	init(&e_attr);
	create_cmd_from_arg(argc, argv, e_attr);
	if (is_self_cmd(argv[1]))
		execute_self(e_attr);
	else
		execute_builtin(e_attr);
	return (0);
}

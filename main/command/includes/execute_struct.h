/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:44:58 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 13:22:44 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_STRUCT_H
# define EXECUTE_STRUCT_H

# include "libft.h"

typedef struct s_exec_attr
{
	char *const	*command;
	char		*infile;
	char		*outfile;
	t_list		*env_lst;
	t_list		*export_lst;
}	t_exec_attr;

#endif


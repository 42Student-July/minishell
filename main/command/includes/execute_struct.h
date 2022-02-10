/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:44:58 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/09 15:49:02 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_STRUCT_H
# define EXECUTE_STRUCT_H

# include "../lib/ft_lst/ft_lst.h"

typedef struct s_exec_attr
{
	char *const	*command;
	char		*infile;
	char		*outfile;
	t_lst		*env_lst;
	t_lst		*export_lst;
}	t_exec_attr;

typedef struct s_kvs
{
	char	*key;
	char	*value;
}	t_kvs;

#endif


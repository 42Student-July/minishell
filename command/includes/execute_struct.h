/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:44:58 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/14 17:16:43 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_STRUCT_H
# define EXECUTE_STRUCT_H

# include "libft.h"

typedef void(*	t_content_f)(void *);

// typedef struct s_exec_attr
// {
// 	char *const	*command;
// 	char		*infile;
// 	char		*outfile;
// 	t_list		*env_lst;
// 	t_list		*export_lst;
// }	t_exec_attr;

typedef struct s_exec_attr
{
	t_list	*cmd;
	t_list	*env_lst;
	t_list	*export_lst;
	int		pipe_count;
}	t_exec_attr;

typedef struct s_kvs
{
	char	*key;
	char	*value;
}	t_kvs;

typedef struct s_env
{
	t_list		*env_lst;
	t_list		*export_lst;
}	t_env;


#endif


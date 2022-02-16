/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:44:58 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/16 09:53:06 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_STRUCT_H
# define EXECUTE_STRUCT_H

# include "libft.h"
# include "parser/parser.h"

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
	t_list	*cmd_lst;
	t_list	*env_lst;
	t_list	*export_lst;
	int		pipe_count;
}	t_exec_attr;

typedef struct s_env
{
	t_list		*env_lst;
	t_list		*export_lst;
}	t_env;

// exec_attribute_utils.c
t_cmd		*get_cmd(t_exec_attr *ea);
char		*get_cmd_name(t_list *cmd);
char		**get_args(t_list *cmd, t_exec_attr *ea);
char		*get_cmd_arg(t_list *cmd, t_exec_attr *ea);
char		*get_cmd_args(t_cmd *cmd, t_exec_attr *ea);
char		*get_argv_one(t_cmd *cmd);

#endif


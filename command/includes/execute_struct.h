/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:44:58 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/26 14:48:11 by tkirihar         ###   ########.fr       */
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
	int		stdfd[3];
}	t_exec_attr;

typedef struct s_env
{
	t_list		*env_lst;
	t_list		*export_lst;
}	t_env;

typedef struct s_pipe_attr
{
	int		cmd_i;
	t_cmd	*current_cmd;
	int		**pipe_fd;
	int		pipe_count;
	int		*cpid_array;
}	t_pipe_attr;

// exec_attribute_utils.c
t_cmd		*get_cmd(t_exec_attr *ea);
char		*get_cmd_name(t_list *cmd);
char		*get_argv_one(t_cmd *cmd);

// redirect_process.c
void		redirect(t_cmd *cmd, t_exec_attr *ea);
bool		has_redirect_file(t_cmd *cmd);
void		redirect_dev_null(t_exec_attr *ea);
void		reset_redirect(t_exec_attr *ea);

#endif


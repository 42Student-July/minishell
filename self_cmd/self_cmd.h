/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:49:42 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/17 15:10:50 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELF_CMD_H
# define SELF_CMD_H

# include <errno.h>

# include "execute_struct.h"
# include "libft.h"
# include "error_handle.h"
# include "environ.h"
# include <limits.h>

# define CD "cd"
# define ECHO "echo"
# define PWD "pwd"
# define EXIT "exit"
# define ENV "env"
# define EXPORT "export"
# define UNSET "unset"
# define CMD_ARG 1

// self_pwd.c
void		exec_self_pwd(t_cmd *cmd, t_exec_attr *ea);

// self_cd.c
void		exec_self_cd(t_cmd *cmd, t_exec_attr *ea);

// self_echo.c
void		exec_self_echo(t_cmd *cmd, t_exec_attr *ea);

// self_exit.c
void		exec_self_exit(t_cmd *cmd, t_exec_attr *ea);

// self_env.c
void		exec_self_env(t_cmd *cmd, t_exec_attr *ea);
void		print_all_env_lst(t_exec_attr *ea);
void		print_env_kvs(void *content);

// self_unset.c
void		exec_self_unset(t_cmd *cmd, t_exec_attr *ea);

// self_export.c
void		exec_self_export(t_cmd *cmd, t_exec_attr *ea);
void		store_arg_only_export(t_exec_attr *ea, char *key);
int			check_export_arg(char **arg);
void		export_with_args(char *arg, t_exec_attr *ea);
bool		addlst_sort_by_ascii(t_list **export_lst, char **arg);

// self_export_utils.c
void		print_export_kvs(void *content);
void		sort_listkey_by_ascii(t_list *export_lst);
void		print_all_export_lst(t_exec_attr *ea);

// self_cmd_utils.c
bool		is_invalid_name(char *name);
void		print_error_msg_with_var(char *cmd_name, char *var);

#endif

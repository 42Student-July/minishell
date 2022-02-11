/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:59:10 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/11 14:25:13 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>

# include "libft.h"
# include "color.h"
# include "execute_struct.h"
# include "environ.h"
# include "self_cmd.h"
# include "error_handle.h"
# include "parser/parser.h"

# define CD "cd"
# define ECHO "echo"
# define PWD "pwd"
# define EXIT "exit"
# define ENV "env"
# define EXPORT "export"
# define UNSET "unset"
# define MY_COMMAND_NUM 4
# define CMD_NAME 0
# define CMD_ARG 1
# define EQUAL 1
# define LF 1

// execute.c
int			execute_cmd(t_list *cmd);
void		print_cmdv(char **cmdv);

// execute_self.c
bool		is_self_cmd(const char *c);
void		execute_self(t_exec_attr *ea);
void		create_cmd_from_arg(int argc, const char *argv[], t_exec_attr *ea);
void		exec_in_child_process(t_exec_attr *ea);
bool		exec_in_main_process(t_exec_attr *ea);

// execute_builtin.c
void		execute_builtin(t_exec_attr *ea);
void		x_execve(t_exec_attr *ea);
bool		is_not_exec_path(const char *command);
char		**convert_envlst_to_array(t_exec_attr *ea);
char		*create_environ_line(char *key, char *value, bool is_end);

// create_cmd.c
bool		is_dollar(char *arg);
char		*convert_env_var(t_exec_attr *ea, char *arg);
void		create_cmd_from_arg(int argc, const char **argv, t_exec_attr *ea);

// redirect_process.c
void		change_direction(t_exec_attr *ea);
bool		is_redirect_flag(t_exec_attr *ea);

// init.c
void		init(t_exec_attr **ea);

// convert_arglst_to_array.c
char		**convert_arglst_to_array(t_redirect_cmd *rc);

// pipe_process.c
void		pipe_process(t_list *cmd, int pipe_cnt);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:25:57 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 14:14:52 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLE_H
# define ERROR_HANDLE_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>

# include "execute_struct.h"

# define MALLOC_ERROR "malloc failed\n"
# define FORK_ERROR "fork error\n"
# define WAIT_ERROR "wait error\n"
# define INVALID_IDENTIFER_MSG "not an identifier\n"

// error_handling.c
void		free_exec_attr(t_exec_attr *ea);
void		free_char_dptr(char **split);
void		abort_minishell(char *msg, t_exec_attr *ea);
void		abort_minishell_with(char *msg, t_exec_attr *ea, char **split);

// debug.c
void		print_command_debug(t_exec_attr *ea);
void		print_kvs_debug(void *content);
void		print_array(char **array);
#endif

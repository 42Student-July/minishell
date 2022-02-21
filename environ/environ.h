/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:38:45 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/19 15:57:07 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# define KEY 0
# define VALUE 1

# include <stdbool.h>

# include "libft.h"
# include "execute_struct.h"
# include "error_handle.h"
# include "self_cmd.h"

# define DQUOTE 2
# define NULL_CHAR 1

// env_lst.c
void		store_allenv_in_envlst(t_exec_attr *ea, char **environ);
bool		store_arg_in_env(t_exec_attr *ea, char *key, char *value);

// export_lst.c
char		*create_export_value(char *value);
void		store_allenv_in_export(t_exec_attr *ea, char **environ);
bool		store_arg_in_export(t_exec_attr *ea, char *key, char *value);

// kvs_utils.c
bool		is_lvalue_bigger_ascii(char *lvalue, char *rvalue);
bool		is_same_str(char *a, char *b);

// lst_utils.c
t_list		*get_list_by_min_ascii_key(t_list *lst);
void		del_lst_by_key(t_list *lst, char *key);
bool		swap_lst_content(t_list *a, t_list *b);
t_list		*get_lst_by_key(t_list *lst, char *key);
void		sort_listkey_by_ascii(t_list *lst);

// lst_utils.c
bool		update_value(t_list *lst, char *key, char *new_v, t_exec_attr *ea);


#endif

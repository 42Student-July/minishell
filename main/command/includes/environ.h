/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:38:45 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/09 15:57:45 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# define KEY 0
# define VALUE 1

# include "execute_struct.h"

// env_lst.c
void		store_env(t_exec_attr *ea, char **environ);

// export_lst.c
char		*create_export_value(char *value);
void		store_export(t_exec_attr *ea, char **environ);

// kvs_utils.c
void		free_all_kvs(t_kvs *kvs);
char		*get_value(void *content);
char		*get_key(void *content);
bool		is_lvalue_bigger_ascii(char *lvalue, char *rvalue);
bool		is_same_key(char *a, char *b);
void		*create_kvs_content(char *key, char *value);

// lst_utils.c
t_lst		*get_lst_by_min_ascii_key(t_lst *lst);
void		del_lst_by_key(t_lst *lst, char *key);
bool		swap_lst_content(t_lst *a, t_lst *b);
t_lst		*get_lst_by_key(t_lst *lst, char *key);

#endif

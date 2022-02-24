/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Cr*eated: 2022/02/05 13:42:08 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/05 13:45:13 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

// void	init(t_exec_attr **ea)
// {
// 	extern char	**environ;

// 	*ea = (t_exec_attr *)malloc(sizeof(t_exec_attr));
// 	if (*ea == NULL)
// 		abort_minishell(MALLOC_ERROR, *ea);
// 	(*ea)->infile = NULL;
// 	(*ea)->outfile = NULL;
// 	store_allenv_in_envlst(*ea, environ);
// 	store_allenv_in_export(*ea, environ);
// }

void	init_oldpwd(t_exec_attr *ea)
{
	t_list *oldpwd;
	
	oldpwd = get_lst_by_key(ea->env_lst, "OLDPWD");
	ft_lstdel(ea->env_lst, oldpwd);
	oldpwd = get_lst_by_key(ea->export_lst, "OLDPWD");
	ft_lstdel(ea->export_lst, oldpwd);
	store_arg_in_export(ea, "OLDPWD", NULL);
}

void	init_new(t_exec_attr **ea)
{
	extern char	**environ;
	
	*ea = (t_exec_attr *)malloc(sizeof(t_exec_attr));
	if (*ea == NULL)
		abort_minishell(MALLOC_ERROR, *ea);
	store_allenv_in_envlst(*ea, environ);
	store_allenv_in_export(*ea, environ);
	init_oldpwd(*ea);
}

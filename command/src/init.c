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
	store_arg_in_env(ea, "OLDPWD", NULL);
	ea->current_pwd = getcwd(NULL, 0);
}

// どこに置けばいいかわかりません by桐原
void	store_stdfd(t_exec_attr *ea)
{
	ea->stdfd[0] = dup(STDIN_FILENO);
	ea->stdfd[1] = dup(STDOUT_FILENO);
	ea->stdfd[2] = dup(STDERR_FILENO);
}

void increment_shlvl(t_exec_attr *ea)
{
	t_kvs *shlvl;
	char *value;

	shlvl = ft_kvsget_elm(ea->env_lst, "SHLVL");
	if (shlvl == NULL)
	{
		shlvl = ft_kvsnew("SHLVL", "1");
		ft_lstadd_back(&ea->env_lst, ft_lstnew(shlvl));
	}
	else
	{
		value = shlvl->value;
		shlvl->value = ft_itoa(ft_atoi(shlvl->value) + 1);
		free(value);
	}
}

void	init_new(t_exec_attr **ea)
{
	extern char	**environ;

	*ea = (t_exec_attr *)malloc(sizeof(t_exec_attr));
	if (*ea == NULL)
		abort_minishell(MALLOC_ERROR, *ea);
	store_allenv_in_envlst(*ea, environ);
	store_allenv_in_export(*ea, environ);
	store_stdfd(*ea);
	init_oldpwd(*ea);
	increment_shlvl(*ea);
}

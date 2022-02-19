/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:54 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/19 15:57:49 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	update_all_environ(char *pwd, t_exec_attr *ea)
{
	char	*export_pwd;
	char	*export_oldpwd;
	char	*old_pwd;

	// OLDPWDは前のPWDからパクって来る
	old_pwd = ft_kvsget_value(get_lst_by_key(ea->env_lst, "PWD")->content);
	export_oldpwd = ft_kvsget_value \
		(get_lst_by_key(ea->export_lst, "PWD")->content);
	update_value(ea->env_lst, "OLDPWD", old_pwd, ea);
	update_value(ea->env_lst, "PWD", pwd, ea);
	export_pwd = create_export_value(pwd);
	if (export_pwd == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	update_value(ea->export_lst, "OLDPWD", export_oldpwd, ea);
	update_value(ea->export_lst, "PWD", pwd, ea);
}

int	x_chdir(char *path, t_exec_attr *ea)
{
	char	pwd[PATH_MAX];

	redirect_dev_null(ea);
	if (chdir(path) == -1)
	{		
		revert_redirect_out(ea);
		print_error(CD, path);
		return (1);
	}
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		revert_redirect_out(ea);
		print_error(PWD, path);
		return (1);
	}
	revert_redirect_out(ea);
	// printf("old_pwd : %s\n", old_pwd);
	// printf("pwd : %s\n", pwd);
	update_all_environ(pwd, ea);
	return (0);
}

int	exec_self_cd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;

	argv_one = get_argv_one(cmd);
	if (argv_one == NULL)
		return (1);
	// TODO: 引数が２つある場合などにも対応する
	return (x_chdir(argv_one, ea));
}

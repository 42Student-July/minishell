/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:54:54 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/18 10:33:59 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

void	update_all_environ(char *pwd, char *oldpwd, t_exec_attr *ea)
{
	char	*export_pwd;
	char	*export_oldpwd;

	update_value(ea->env_lst, "OLDPWD", oldpwd, ea);
	update_value(ea->env_lst, "PWD", pwd, ea);
	export_pwd = create_export_value(pwd);
	if (export_pwd == NULL)
		abort_minishell(MALLOC_ERROR, ea);
	export_oldpwd = create_export_value(oldpwd);
	if (export_oldpwd == NULL)
	{
		free(export_pwd);
		abort_minishell(MALLOC_ERROR, ea);
	}
	update_value(ea->export_lst, "OLDPWD", oldpwd, ea);
	update_value(ea->export_lst, "PWD", pwd, ea);
}

void	x_chdir(char *path, t_exec_attr *ea)
{
	char	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];

	redirect_dev_null(ea);
	if (getcwd(old_pwd, PATH_MAX) == NULL)
		abort_minishell(GETCWD_ERROR, ea);
	if (chdir(path) == -1)
	{
		print_error(CD, path);
		return ;
	}
	if (getcwd(pwd, PATH_MAX) == NULL)
		abort_minishell(GETCWD_ERROR, ea);
	revert_redirect_out(ea);
	// printf("old_pwd : %s\n", old_pwd);
	// printf("pwd : %s\n", pwd);
	update_all_environ(pwd, old_pwd, ea);
}

void	exec_self_cd(t_cmd *cmd, t_exec_attr *ea)
{
	char	*argv_one;

	argv_one = get_argv_one(cmd);
	if (argv_one == NULL)
		return ;
	(void)ea;
	// TODO: 引数が２つある場合などにも対応する
	x_chdir(argv_one, ea);
}

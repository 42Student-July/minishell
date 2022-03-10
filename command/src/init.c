
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
	ft_kvsdelete(oldpwd->content);
	ft_lstdel(ea->env_lst, oldpwd);
	oldpwd = get_lst_by_key(ea->export_lst, "OLDPWD");
	ft_kvsdelete(oldpwd->content);
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
}

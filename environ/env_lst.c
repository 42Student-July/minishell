/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:20:16 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/14 17:01:49 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

void	store_allenv_in_envlst(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**split;
	t_list		*env_lst;

	i = 0;
	env_lst = NULL;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (split == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		if (!ft_lstadd_back(&env_lst, \
			ft_lstnew(ft_kvsnew(split[KEY], split[VALUE]))))
			abort_minishell_with(MALLOC_ERROR, ea, split);
		i++;
		free_char_dptr(split);
	}
	ea->env_lst = env_lst;
}

bool	store_arg_in_env(t_exec_attr *ea, char *key, char *value)
{
	return (ft_lstadd_back(&ea->env_lst, \
		ft_lstnew(ft_kvsnew(key, value))));
}

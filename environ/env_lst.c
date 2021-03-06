
#include "environ.h"

void	store_allenv_in_envlst(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**split;
	t_list		*env_lst;
	char		*tmp;

	i = 0;
	env_lst = NULL;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (split == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		if (split[VALUE] == NULL)
		{
			// valueがnullのときはsplit[VALUE]に値を入れるとreallocが必要なのでtmpを用意
			tmp = ft_strdup("");
			if (!ft_lstadd_back(&env_lst, ft_lstnew(ft_kvsnew(split[KEY], tmp))))
				abort_minishell_with(MALLOC_ERROR, ea, split);
			free(tmp);
		}
		else
		{
			if (!ft_lstadd_back(&env_lst, \
			ft_lstnew(ft_kvsnew(split[KEY], split[VALUE]))))
				abort_minishell_with(MALLOC_ERROR, ea, split);

		}
		i++;
		free_char_dptr(split);
	}
	ea->env_lst = env_lst;
}

bool	store_arg_in_env(t_exec_attr *ea, char *key, char *value)
{
	t_list	*target;

	target = get_lst_by_key(ea->env_lst, key);
	if (target != NULL)
	{
		if (!update_value(ea->env_lst, key, value, ea))
			return (false);
	}
	else
	{
		ft_lstadd_back(&ea->env_lst, \
			ft_lstnew(ft_kvsnew(key, value)));
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:19:25 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/11 13:33:33 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

char	*create_export_value(char *value)
{
	// 合成して ex)declare -x key="value"を作る
	char 		*new_value;
	size_t		new_value_len;
	size_t		value_len;

	if (value == NULL)
		value_len = 0;
	else
		value_len = ft_strlen(value);
	new_value_len = (value_len + DQUOTE + NULL_CHAR);
	new_value = (char *)malloc(sizeof(char) * new_value_len);
	if (new_value == NULL)
		return (NULL);
	ft_strlcat(new_value, "\"", new_value_len);
	ft_strlcat(new_value, value, new_value_len);
	ft_strlcat(new_value, "\"", new_value_len);
	return (new_value);
}

void	store_allenv_in_export(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**split;
	t_list		*export_lst;
	char		*value;

	export_lst = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (split == NULL)
			abort_minishell(MALLOC_ERROR, ea);
		value = create_export_value(split[VALUE]);
		if (value == NULL)
			abort_minishell_with(MALLOC_ERROR, ea, split);
		if (!store_arg_in_export(ea, split[KEY], value))
			abort_minishell_with(MALLOC_ERROR, ea, split);
		free_char_dptr(split);
		free(value);
		i++;
	}
	ea->export_lst = export_lst;
}

bool	store_arg_in_export(t_exec_attr *ea, char *key, char *value)
{
	if (!ft_lstadd_back(&ea->export_lst, \
			ft_lstnew(ft_kvsnew(key, value))))
		return (false);
	sort_listkey_by_ascii(ea->export_lst);
	return (true);
}

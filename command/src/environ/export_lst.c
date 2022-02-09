/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:19:25 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/09 15:47:44 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

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

void	store_export(t_exec_attr *ea, char **environ)
{
	size_t		i;
	char		**split;
	t_lst		*export_lst;
	bool		flag;
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
		flag = ft_lstadd_back(&export_lst, \
		ft_lstnew(create_kvs_content(split[KEY], value)));
		if (!flag)
			abort_minishell_with(MALLOC_ERROR, ea, split);
		i++;
		free_char_dptr(split);
	}
	sort_lstkey_by_ascii(export_lst);
	ea->export_lst = export_lst;
}

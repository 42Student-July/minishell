/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:47:13 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 10:18:31 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	free_all_kvs(t_kvs *kvs)
{
	if (kvs != NULL)
	{
		if (kvs->key != NULL)
			free(kvs->key);
		if (kvs->value != NULL)
			free(kvs->value);
		free(kvs);
	}
}

void	*create_content(char *key, char *value)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)malloc(sizeof(t_kvs));
	if (kvs == NULL)
		return (NULL);
	kvs->key = ft_strdup(key);
	if (kvs->key == NULL)
		return (NULL);
	kvs->value = ft_strdup(value);
	if (kvs->value == NULL)
	{
		free(kvs->key);
		return (NULL);
	}
	return ((void *)kvs);
}

int	main(void)
{
	int			i;
	extern char	**environ;
	char		**line;
	t_list		*env_lst;
	t_content_f	f;

	i = 0;
	f = print_kvs_debug;
	env_lst = NULL;
	while (environ[i] != NULL)
	{
		line = ft_split(environ[i], '=');
		if (line == NULL)
			exit(1);
		ft_lstadd_back(&env_lst, \
		ft_lstnew(create_content(line[KEY], line[VALUE])));
		if (env_lst == NULL)
			exit(1);
		i++;
		free(line);
	}
	ft_lstiter(env_lst, f);

	return (0);
}

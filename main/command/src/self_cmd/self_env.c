/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:36:05 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 10:18:31 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

// TODO:引数あるバージョンは未対応
void	exec_self_env(t_exec_attr *ea)
{
	print_all_env_lst(ea);
}

void	print_all_env_lst(t_exec_attr *ea)
{
	t_content_f	f;

	f = print_env_kvs;
	ft_lstiter(ea->env_lst, f);
}

void	print_env_kvs(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	if (kvs->value == NULL)
		printf("%s=\n", kvs->key);
	else
		printf("%s=%s\n", kvs->key, kvs->value);
}

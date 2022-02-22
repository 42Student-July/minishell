/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:36:05 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/18 00:34:31 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

// TODO:引数あるバージョンは未対応
int	exec_self_env(t_cmd *cmd, t_exec_attr *ea)
{
	(void)cmd;
	print_all_env_lst(ea);
	return (0);
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

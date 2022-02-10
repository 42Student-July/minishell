/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:24:01 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 10:18:31 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/command.h"

void	print_all_export_list(t_exec_attr *ea)
{
	t_content_f	f;

	f = print_export_kvs;
	ft_lstiter(ea->export_list, f);
}

void	print_export_kvs(void *content)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)content;
	if (kvs->value == NULL)
		printf("declare -x %s\n", kvs->key);
	else
		printf("declare -x %s=%s\n", kvs->key, kvs->value);
}

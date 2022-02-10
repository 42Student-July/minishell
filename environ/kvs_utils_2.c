/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvs_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:36:14 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/10 15:36:48 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

void	*create_kvs_content(char *key, char *value)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)malloc(sizeof(t_kvs));
	if (kvs == NULL)
		return (NULL);
	kvs->key = ft_strdup(key);
	if (kvs->key == NULL)
		return (NULL);
	// export k のような形で入る場合を考慮して、valueはnullを許容する
	if (value != NULL)
	{
		kvs->value = ft_strdup(value);
		if (kvs->value == NULL)
		{
			free(kvs->key);
			return (NULL);
		}
	}
	else
		kvs->value = NULL;
	return ((void *)kvs);
}

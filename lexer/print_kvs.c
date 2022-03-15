/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_kvs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito     <akito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:12 by akito             #+#    #+#             */
/*   Updated: 2022/03/15 14:17:12 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include <stdio.h>

void	print_kvs(t_list *lst)
{
	t_list	*tmp;
	t_kvs	*kvs;

	tmp = lst;
	while (tmp != NULL)
	{
		kvs = (t_kvs *)tmp->content;
		printf("%s: %s\n", kvs->key, kvs->value);
		tmp = tmp->next;
	}
}

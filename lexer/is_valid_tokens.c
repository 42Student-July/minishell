/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito     <akito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:12 by akito             #+#    #+#             */
/*   Updated: 2022/03/15 14:17:12 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_valid_tokens(t_list *token_list)
{
	while (token_list != NULL)
	{
		if (((t_token *)token_list->content)->type == TOKEN_ILLEGAL)
			return (false);
		token_list = token_list->next;
	}
	return (true);
}

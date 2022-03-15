/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_literal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito     <akito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:12 by akito             #+#    #+#             */
/*   Updated: 2022/03/15 14:17:12 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "lexer.h"
#include "libft.h"

char	*get_literal(t_token *token)
{
	if (is_word_token(token->type))
		return (ft_strdup(token->literal));
	else
		exit(EXIT_FAILURE);
	return (NULL);
}

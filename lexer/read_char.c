/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito     <akito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:12 by akito             #+#    #+#             */
/*   Updated: 2022/03/15 14:17:12 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

void	read_char(t_lexer *lexer)
{
	if (lexer->read_position >= ft_strlen(lexer->input))
	{
		lexer->ch = '\0';
	}
	else
	{
		lexer->ch = lexer->input[lexer->read_position];
	}
	lexer->position = lexer->read_position;
	lexer->read_position++;
}

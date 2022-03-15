/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito     <akito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:12 by akito             #+#    #+#             */
/*   Updated: 2022/03/15 14:17:12 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

void	delete_lexer(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free(lexer->input);
	lexer->input = NULL;
	ft_lstclear(&lexer->io_here_delimiters, free);
	ft_lstclear(&lexer->heredocs, ft_kvsdelete);
	free(lexer);
	return ;
}

void	delete_lexer_without_heredocs(t_lexer *lexer)
{
	if (lexer == NULL)
		return ;
	free(lexer->input);
	lexer->input = NULL;
	ft_lstclear(&lexer->io_here_delimiters, free);
	free(lexer);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito     <akito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:12 by akito             #+#    #+#             */
/*   Updated: 2022/03/15 14:17:12 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token	*peek_from_redirect_out(t_lexer *lexer)
{
	t_token	*token;

	if (peek_char(lexer) == '>')
	{
		read_char(lexer);
		token = new_token(TOKEN_REDIRECT_APPEND, ">>");
	}
	else
		token = new_token(TOKEN_REDIRECT_OUT, ">");
	return (token);
}

t_token	*peek_from_redirect_in(t_lexer *lexer)
{
	t_token	*token;

	if (peek_char(lexer) == '<')
	{
		read_char(lexer);
		add_heredoc_delimiter(lexer);
		token = new_token(TOKEN_HEREDOC, "<<");
	}
	else
		token = new_token(TOKEN_REDIRECT_IN, "<");
	return (token);
}

t_token	*next_token(t_lexer *lexer)
{
	t_token	*token;

	skip_whitespace(lexer);
	if (lexer->ch == '\0')
		token = new_token(TOKEN_EOF, NULL);
	else if (lexer->ch == '>')
		token = peek_from_redirect_out(lexer);
	else if (lexer->ch == '<')
	{
		token = peek_from_redirect_in(lexer);
		if (token->type == TOKEN_ILLEGAL || token->type == TOKEN_HEREDOC)
			return (token);
	}
	else if (lexer->ch == '|')
		token = new_token(TOKEN_PIPE, "|");
	else if (!ft_isspace(lexer->ch))
		return (new_ident_token(lexer));
	else
		token = new_token(TOKEN_ILLEGAL, NULL);
	read_char(lexer);
	return (token);
}

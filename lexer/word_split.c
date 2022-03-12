#include <stdio.h>
#include "lexer.h"
#include "libft.h"

char	*new_literal(const char *str, size_t *pos)
{
	size_t	i;
	size_t	j;
	char	is_quoted;

	i = 0;
	is_quoted = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (is_quoted == str[i])
				is_quoted = '\0';
			else if (is_quoted == '\0')
				is_quoted = str[i];
		}
		if (!is_quoted && !ft_isspace(str[i]))
			break ;
		i++;
	}
	j = 0;
	while (str[i + j] != '\0' && !ft_isspace(str[i + j]))
		j++;
	*pos = i + j;
	return (ft_substr(str, i, j));
}

void	split_token(t_list **lst, t_token **token)
{
	char	*str;
	char	*str_next;
	size_t	pos;

	str = new_literal((*token)->literal, &pos);
	str_next = ft_substr((*token)->literal, pos,
			ft_strlen((*token)->literal));
	free((*token)->literal);
	(*token)->literal = str;
	if (*str_next == '\0')
		delete_str(&str_next);
	else
	{
		*token = new_token(TOKEN_IDENT, str_next);
		free(str_next);
		ft_lstadd_next(*lst, *token);
	}
}

void	split_process(t_list **lst, t_token **token)
{
	if (has_only_whitespace((*token)->literal))
	{
		delete_str(&((*token)->literal));
		*lst = (*lst)->next;
		return ;
	}
	if (has_whitespace((*token)->literal))
		split_token(lst, token);
}

void	word_split(t_list *lst)
{
	t_token	*token;

	while (lst != NULL)
	{
		token = lst->content;
		if (token->type == TOKEN_IDENT)
			split_process(&lst, &token);
		lst = lst->next;
	}
}

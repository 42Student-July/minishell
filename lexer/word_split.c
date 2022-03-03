#include <stdio.h>
#include "lexer.h"
#include "libft.h"

void	ft_lstadd_next(t_list *lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	new->next = lst->next;
	lst->next = new;
}

bool has_only_whitespace(const char *str)
{
	while(*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	has_whitespace(const char *str)
{
	size_t	i;
	char is_quoted;

	i = 0;
	is_quoted = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (is_quoted == '\0')
				is_quoted = str[i];
			else if (is_quoted == str[i])
				is_quoted = '\0';
		}
		if (!is_quoted && ft_isspace(str[i]))
			return (true);
		i++;
	}
	return (false);
}

char	*new_literal(const char *str, size_t *pos)
{
	size_t	i;
	size_t	j;
	char is_quoted;

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
			break;
		i++;
	}
	j = 0;
	while (str[i + j] != '\0' && !ft_isspace(str[i + j]))
		j++;
	*pos = i + j;
	return (ft_substr(str, i, j));
}

void	word_split(t_list *lst)
{
	t_token	*token;
	char	*str;
	char	*str_next;
	size_t	pos;

	while (lst != NULL)
	{
		token = lst->content;
		if (token->type == TOKEN_IDENT)
		{
			if (has_only_whitespace(token->literal))
			{
				free(token->literal);
				token->literal = NULL;
				lst = lst->next;
				continue;
			}
			if (has_whitespace(token->literal))
			{
				str = new_literal(token->literal, &pos);
				str_next = ft_substr(token->literal, pos,
						ft_strlen(token->literal));
				free(token->literal);
				token->literal = str;
				if (*str_next == '\0')
				{
					free(str_next);
					str_next = NULL;
				} else {
					token = new_token(TOKEN_IDENT, str_next);
					free(str_next);
					ft_lstadd_next(lst, token);
				}
			}
		}
		lst = lst->next;
	}
}

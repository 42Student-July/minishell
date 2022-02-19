#include "lexer.h"
#include "libft.h"

void	ft_lstadd_next(t_list *lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	new->next = lst->next;
	lst->next = new;
}

bool	has_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]))
			return (true);
		i++;
	}
	return (false);
}

char	*new_literal(const char *str, size_t *pos)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	j = 0;
	while (str[i + j] != '\0' && !ft_isspace(str[i + j]))
		j++;
	*pos = i + j;
	return (ft_substr(str, i, i + j));
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
			if (has_whitespace(token->literal))
			{
				str = new_literal(token->literal, &pos);
				str_next = ft_substr(token->literal, pos,
						ft_strlen(token->literal));
				free(token->literal);
				token->literal = str;
				token = new_token(TOKEN_IDENT, str_next);
				ft_lstadd_next(lst, token);
			}
		}
		lst = lst->next;
	}
}

#include "lexer.h"
#include "libft.h"

void	delete_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	ft_lstadd_next(t_list *lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	new->next = lst->next;
	lst->next = new;
}

bool	has_only_whitespace(const char *str)
{
	while (*str)
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
	char	is_quoted;

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

size_t	splitted_token_count(const char *str)
{
	size_t	i;
	char	is_quoted;

	i = 0;
	is_quoted = '\0';
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
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
			break ;
		i++;
	}
	return (1 + splitted_token_count(str + i));
}

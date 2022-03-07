#include "lexer.h"
#include "libft.h"

char	*join_string(char *a, char *b)
{
	char	*c;

	if (!a || !b)
		exit(EXIT_FAILURE);
	c = ft_strjoin(a, b);
	if (!c)
		exit(EXIT_FAILURE);
	free(a);
	free(b);
	return (c);
}

void	expand_single_quote(char **str_p, size_t *i, const char quote)
{
	size_t	j;
	char	*str;
	char	*tmp_front;
	char	*tmp_middle;
	char	*tmp_back;

	j = *i + 1;
	str = *str_p;
	while (str[j] != '\0' && str[j] != quote)
		j++;
	if (str[j] == '\0')
		exit(EXIT_FAILURE);
	tmp_front = ft_substr(str, 0, *i);
	if (tmp_front == NULL)
		exit(EXIT_FAILURE);
	tmp_middle = ft_substr(str, *i + 1, j - *i - 1);
	if (tmp_middle == NULL)
		exit(EXIT_FAILURE);
	tmp_back = ft_substr(str, j + 1, ft_strlen(str) - j);
	if (tmp_back == NULL)
		exit(EXIT_FAILURE);
	free(*str_p);
	*str_p = join_string(join_string(tmp_front, tmp_middle), tmp_back);
	*i = j - 1;
}

char	*expand_quote_str(const char *input)
{
	char	*str;
	size_t	i;

	str = ft_strdup(input);
	if (str == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			expand_single_quote(&str, &i, str[i]);
		else
			i++;
	}
	return (str);
}

void	expand_quote(void *token_p)
{
	t_token	*token;
	char	*str;

	token = (t_token *)token_p;
	if (token->type == TOKEN_IDENT)
	{
		if (token->literal != NULL)
		{
			str = expand_quote_str(token->literal);
			free(token->literal);
			token->literal = str;
		}
	}
}

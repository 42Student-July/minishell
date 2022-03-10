
#include "libft.h"
#include <stdlib.h>

char		**ft_split(char const *s, char c);
static int	count_cols(const char *str, char c);
static char	*ft_strcdup(const char *str, char c);
static char	**set_words(char **res, const char *str,
				const size_t col, const char c);
static char	**clear_all(char **res, size_t col_i);

char	**ft_split(char const *str, char c)
{
	char	**res;
	size_t	col;

	if (str == NULL)
		return (NULL);
	col = count_cols(str, c);
	res = (char **)malloc(sizeof(char *) * (col + 1));
	if (res == NULL)
		return (NULL);
	res = set_words(res, str, col, c);
	if (res == NULL)
		return (NULL);
	res[col] = NULL;
	return (res);
}

static int	count_cols(const char *str, char c)
{
	size_t	i;
	size_t	col;

	i = 0;
	col = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			col++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (col);
}

static char	*ft_strcdup(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	return (ft_substr(str, 0, len));
}

static char	**set_words(char **res, const char *str,
			const size_t col, const char c)
{
	size_t	str_i;
	size_t	col_i;

	str_i = 0;
	col_i = 0;
	while (col_i < col)
	{
		if (str[str_i] == c)
		{
			str_i++;
			continue ;
		}
		res[col_i] = ft_strcdup(str + str_i, c);
		if (res[col_i] == NULL)
			return (clear_all(res, col_i));
		str_i += ft_strlen(res[col_i]);
		col_i++;
	}
	return (res);
}

static char	**clear_all(char **res, size_t col_i)
{
	while (col_i > 0)
	{
		free(res[col_i - 1]);
		res[col_i - 1] = NULL;
		col_i--;
	}
	free(res);
	return (NULL);
}

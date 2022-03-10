
#include "libft.h"
static int	contains_charset(const char c, const char *charset);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	prefix_len;
	size_t	suffix_len;
	size_t	res_len;
	size_t	s1_len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	prefix_len = 0;
	s1_len = ft_strlen(s1);
	while (contains_charset(s1[prefix_len], set) != 0)
		prefix_len++;
	if (prefix_len == s1_len)
		return (ft_strdup(""));
	suffix_len = 0;
	while (contains_charset(s1[s1_len - 1 - suffix_len], set) != 0)
		suffix_len++;
	res_len = s1_len - (prefix_len + suffix_len);
	return (ft_substr(s1, prefix_len, res_len));
}

static int	contains_charset(const char c, const char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

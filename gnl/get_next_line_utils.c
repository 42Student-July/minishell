
#include "get_next_line.h"

size_t	ft_gnl_strlen(const char *str)
{
	size_t	length;

	length = 0;
	if (str == NULL)
		return (0);
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

char	*ft_gnl_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	const size_t	s_len = ft_gnl_strlen(s);

	if (s == NULL)
		return (NULL);
	if (s_len <= (size_t)start)
		return (ft_gnl_strdup(""));
	if (len > s_len - (size_t)start)
		len = s_len - (size_t)start;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_gnl_strlcpy(res, s + start, len + 1);
	return (res);
}

char	*ft_gnl_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	s1_len = ft_gnl_strlen(s1);
	s2_len = ft_gnl_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (res == NULL)
		return (NULL);
	ft_gnl_strlcpy(res, s1, s1_len + 1);
	ft_gnl_strlcpy(res + s1_len, s2, s2_len + 1);
	return (res);
}

char	*ft_gnl_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_gnl_strlcpy(str, s, len + 1);
	return (str);
}

char	*ft_gnl_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

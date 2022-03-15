
#include "libft.h"
#include <stdint.h>
#include <errno.h>
static size_t	ft_min(size_t a, size_t b);
char			*ft_xsubstr(char const *s, unsigned int start, size_t len);

char	*ft_xsubstr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= (size_t)start)
		return (ft_xstrdup(""));
	len = ft_min(len, ft_strlen(s) - (size_t)start);
	res = (char *)ft_xmalloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

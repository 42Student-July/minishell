#include "libft.h"
#include <stdio.h>

char	*ft_xstrdup(const char *s)
{
	char	*str;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	str = (char *)ft_xmalloc(sizeof(char) * (len + 1));
	ft_strlcpy(str, s, len + 1);
	return (str);
}

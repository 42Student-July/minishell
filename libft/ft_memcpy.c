
#include "libft.h"
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*to;
	const unsigned char	*from = (const unsigned char *)src;

	if (dest == NULL && src == NULL)
		return (NULL);
	to = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (dest);
}

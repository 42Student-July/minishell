
#include "libft.h"
int	ft_isprint(int c)
{
	return (0x20 <= c && c <= 0x7e);
}

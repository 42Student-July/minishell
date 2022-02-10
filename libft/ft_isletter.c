#include "libft.h"

int	ft_isletter(int c)
{
	return (ft_isalnum(c) || c == '_');
}

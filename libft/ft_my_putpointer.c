
#include "libft.h"

int64_t	ft_my_putpointer(size_t n)
{
	int64_t	cnt;

	cnt = ft_my_putstr("0x");
	cnt += ft_my_putbase(n, "0123456789abcdef");
	return ((int64_t)cnt);
}

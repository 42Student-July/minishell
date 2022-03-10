
#include "libft.h"
#include <unistd.h>

int64_t	ft_my_putchar(char c)
{
	return (write(1, &c, 1));
}

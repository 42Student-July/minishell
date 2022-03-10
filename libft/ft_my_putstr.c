
#include "libft.h"
#include <unistd.h>

int64_t	ft_my_putstr(const char *str)
{
	if (str == NULL)
		return (ft_my_putstr("(null)"));
	return (write(1, str, ft_strlen(str)));
}

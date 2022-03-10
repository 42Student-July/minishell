
#include "libft.h"

void	ft_kvsreplace_value(void *content, char *new_value)
{
	t_kvs	*k;
	char	*tmp;

	k = (t_kvs *)content;
	tmp = k->value;
	k->value = new_value;
	free(tmp);
}

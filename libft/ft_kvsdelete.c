#include "libft.h"

void	ft_kvsdelete(void *elm)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)elm;
	free(kvs->key);
	kvs->key = NULL;
	free(kvs->value);
	kvs->value = NULL;
	free(kvs);
	kvs = NULL;
}

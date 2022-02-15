#include "libft.h"

void	*ft_kvsnew(char *key, char *value)
{
	t_kvs	*kvs;

	kvs = (t_kvs *)malloc(sizeof(t_kvs));
	if (kvs == NULL)
		return (NULL);
	kvs->key = ft_strdup(key);
	if (kvs->key == NULL)
		return (NULL);
	if (value != NULL)
	{
		kvs->value = ft_strdup(value);
		if (kvs->value == NULL)
		{
			free(kvs->key);
			return (NULL);
		}
	}
	else
		kvs->value = NULL;
	return ((void *)kvs);
}

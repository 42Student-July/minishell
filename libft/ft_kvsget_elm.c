#include "libft.h"

t_kvs	*ft_kvsget_elm(t_list *lst, char *key)
{
	t_list	*ret;

	ret = lst;
	while (ret != NULL)
	{
		if (ft_streq(ft_kvsget_key(ret->content), key))
			return (ret->content);
		ret = ret->next;
	}
	return (NULL);
}

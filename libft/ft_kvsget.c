#include "libft.h"

char	*ft_kvsget(t_list *lst, char *key)
{
	t_list	*ret;

	ret = lst;
	while (ret != NULL)
	{
		if (ft_streq(ft_kvsget_key(ret->content), key))
			return (((t_kvs *)ret->content)->value);
		ret = ret->next;
	}
	return (NULL);
}

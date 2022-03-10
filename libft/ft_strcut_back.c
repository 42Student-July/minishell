
#include "libft.h"

// 後ろから特定の文字を探し、存在した場合その文字を含めたそれ以降の文字をcutする
char	*ft_strcut_back(char *str, char c)
{
	char	*position;
	char	*tmp;
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	tmp = str;
	position = ft_strrchr(str, c);
	if (position == NULL)
		return (NULL);
	while (tmp++ != position)
		i++;
	return (ft_substr(str, 0, i));
}


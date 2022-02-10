#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include "../includes/command.h"

int	main()
{
	size_t		new_value_len;
	const char	*prefix;
	const char	*dquote;
	char 		*value = "TEST";
	char 		*name = "test";
	char		*new_value;
	
	prefix = "declare -x ";
	dquote = "\"";
	// export一行の長さ 
	// prefix + name + = + " + value + " + \n
	// 11 + 可変name + 1 + 1 + 可変value + 1 + 1 → 15 + 可変長
	new_value_len = (EXPORT_CONST_LEN + ft_strlen(name) + ft_strlen(value) + NULL_CHAR);
	new_value = (char *)malloc(sizeof(char) * new_value_len);
	ft_strlcat(new_value, "declare -x ", new_value_len);
	ft_strlcat(new_value, name, new_value_len);
	ft_strlcat(new_value, "=\"", new_value_len);
	ft_strlcat(new_value, value, new_value_len);
	ft_strlcat(new_value, "\"\n", new_value_len);
	printf("new_value : %s\n", new_value);
	free(new_value);
	system("leaks a.out");
	return (0);
}
#include "../includes/command.h"

bool	is_my_command(const char *c)
{
	size_t c_len;

	c_len = ft_strlen(c);
	if (
		ft_strncmp(c, CD, c_len) &&
		ft_strncmp(c, ECHO, c_len) &&
		ft_strncmp(c, PWD, c_len) &&
		ft_strncmp(c, EXIT, c_len)
		)
		return (false);
	return (true);
}

int	main(int argc, const char *argv[])
{
	(void)argc;
	printf(" ft_strncmp(c, ECHO, ft_strlen(ECHO)) = %d\n", ft_strncmp(argv[1], ECHO, ft_strlen(ECHO)));
	if (is_my_command(argv[1]))
	{
		printf("true\n");
	}
	else
		printf("false\n");
	return (0);
}
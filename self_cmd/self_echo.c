
#include "libft.h"
#include "self_cmd.h"
#include <stdbool.h>

int	exec_self_echo(t_cmd *cmd, t_exec_attr *ea)
{
	t_list	*args;
	char	*str;
	int		i;
	bool display_return ;

	args = cmd->args->next;
	(void)ea;
	display_return = false;
	// TODO: pipeでつないだときへの対応、引数が2つの場合にも対応
	while (args != NULL)
	{
		str = args->content;
		if (str == NULL || str[0] != '-')
			break ;
		i = 1;
		while (str[i])
		{
			if (ft_strchr("n", str[i]) == NULL)
				break;
			i++;
		}
		if (str[1] == '\0' || str[i] != '\0')
			break ;
		i = 1;
		while (str[i] != '\0')
		{
			if (str[i] == 'n')
				display_return = true;
			i++;
		}
		args = args->next;
	}
	while (args != NULL)
	{
		str = args->content;
		if (str == NULL)
			break ;
		args = args->next;
		ft_putstr_fd(str, STDOUT_FILENO);
		if (args != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!display_return)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

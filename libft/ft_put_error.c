
#include "libft.h"
#include <unistd.h>

// 第1引数にエラーメッセージ、第２引数にコマンド、なければNULL
void	ft_put_error(char *message)
{
	ft_putstr_fd("bash: ", STDERR_FILENO); // 最後にminishellに変える予定
	ft_putendl_fd(message, STDERR_FILENO);
}

void	ft_put_cmd_error(char *cmd, char *message)
{
	ft_putstr_fd("bash: ", STDERR_FILENO); // 最後にminishellに変える予定
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}

void	ft_put_arg_error(char *cmd, char *arg, char *message)
{
	ft_putstr_fd("bash: ", STDERR_FILENO); // 最後にminishellに変える予定
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}

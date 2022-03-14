
#include "command.h"

t_cmd	*get_cmd(t_exec_attr *ea)
{
	return ((t_cmd *)ea->cmd_lst->content);
}

// コマンド名をgetする
char	*get_cmd_name(t_list *cmd_lst)
{
	t_cmd	*cmd;

	cmd = cmd_lst->content;
	return (cmd->cmd);
}

char	*get_argv_one(t_cmd *cmd)
{
	if (cmd->args == NULL)
	{
		ft_putstr_fd("no command", STDERR_FILENO);
		return (NULL);
	}
	if (cmd->args->next == NULL)
	{
		return (NULL);
	}
	return (cmd->args->next->content);
}

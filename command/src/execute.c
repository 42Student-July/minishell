
#include "command.h"

int	execute_cmd(t_exec_attr *ea)
{
	int	pipe_count;

	if (ea->cmd_lst == NULL)
		return (0);
	pipe_count = ft_lstsize(ea->cmd_lst) - 1;
	if (pipe_count == 0)
	{
		no_pipe_process(ea);
	}
	else
	{
		pipe_process(ea, pipe_count);
	}
	return (0);
}

// int	execute_cmd(t_list *cmd)
// {
// 	t_exec_attr	*e_attr;

// 	(void)cmd;
// 	int argc = 0;
// 	const char **argv = NULL;
// 	init(&e_attr);
// 	create_cmd_from_arg(argc, argv, e_attr);
// 	if (is_self_cmd(argv[1]))
// 		execute_self(e_attr);
// 	else
// 		execute_builtin(e_attr);
// 	return (0);
// }

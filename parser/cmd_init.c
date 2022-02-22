#include "parser.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	return (cmd);
}

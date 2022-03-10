
#include "command.h"

static void	free_pipe_fd(t_pipe_attr *pa)
{
	int	i;

	i = 0;
	while (i < pa->pipe_count)
	{
		free(pa->pipe_fd[i]);
		i++;
	}
	free(pa->pipe_fd);
}

void	free_pipe_attr(t_pipe_attr *pa)
{
	// ここでpa->current_cmdもfreeすべきかも
	free_pipe_fd(pa);
	free(pa->cpid_array);
}

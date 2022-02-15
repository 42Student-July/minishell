#include "parser.h"

static void delete_exec_cmd(t_exec_cmd **cmd)
{
	free((*cmd)->cmd);
	(*cmd)->cmd = NULL;
	ft_lstclear(&(*cmd)->args, free);
	(*cmd)->args = NULL;
	free(*cmd);
	*cmd = NULL;
}

/**
 * @brief
 *
 * typedef struct s_redirect_cmd
{
	int type;
	t_cmd *cmd;
	t_list *filenames_in;
	t_list *filenames_out;
	bool is_double;

} t_redirect_cmd;


 */
static void delete_redirect_cmd(t_redirect_cmd **cmd)
{
	t_cmd *exec_cmd = (t_cmd *)(*cmd)->cmd;

	delete_cmd(&exec_cmd);
	ft_lstclear(&(*cmd)->filenames_in, delete_file);
	ft_lstclear(&(*cmd)->filenames_out, delete_file);
	free(*cmd);
	*cmd = NULL;
}


#include <stdio.h>
void delete_cmd(t_cmd **cmd)
{
	t_exec_cmd *exec_cmd;
	t_redirect_cmd *redirect_cmd;

	if (cmd == NULL || *cmd == NULL)
		return;
	if ((*cmd)->type == CMD_EXEC)
	{
		exec_cmd = (t_exec_cmd *)(*cmd);
		delete_exec_cmd(&exec_cmd);
	}
	if ((*cmd)->type == CMD_REDIRECT)
	{
		redirect_cmd = (t_redirect_cmd *)(*cmd);
		delete_redirect_cmd(&redirect_cmd);
	}
}


void delete_pipe(void *cmd)
{
	t_cmd *redirect_cmd;

	redirect_cmd = (t_cmd *)cmd;
	delete_cmd(&redirect_cmd);
}

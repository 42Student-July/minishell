#include "libft.h"
#include "parser.h"
#include <stdio.h>

void print_files(char *name, t_list *list)
{
	t_list *tmp;
	t_file *file;

	tmp = list;
	printf("%s", name);
	if (tmp == NULL)
		printf("(null)");
	while (tmp != NULL)
	{
		file = (t_file *)tmp->content;
		if (tmp->content == NULL)
			printf("\n");
		printf("(%s,", (char *)file->filename);
		if (file->is_double)
			printf("true),");
		else
			printf("false),");
		tmp = tmp->next;
	}
	printf("\n");
}

void print_lists(char *name, t_list *list)
{
	t_list *tmp;
	char *str;

	tmp = list;
	printf("%s", name);
	if (tmp == NULL)
		printf("(null)");
	while (tmp != NULL)
	{
		str = (char *)tmp->content;
		if (str == NULL)
			printf("\n");
		printf("%s,", str);
		tmp = tmp->next;
	}
	printf("\n");
}


void print_exec_cmd(t_exec_cmd *cmd)
{
	if (cmd->type != CMD_EXEC)
		return;
	printf("\t\texec_cmd: %s\n", cmd->cmd);
	print_lists("\t\targs: ", cmd->args);
}

void print_redirect_cmd(const t_redirect_cmd *cmd)
{
	if (cmd->type != CMD_REDIRECT)
		return;
	print_exec_cmd((t_exec_cmd *)cmd->cmd);
	print_files("\t\tfilenames_in: ", cmd->filenames_in);
	print_files("\t\tfilenames_out: ", cmd->filenames_out);
}



void print_pipe_cmd(t_list *cmd)
{
	const t_redirect_cmd *tmp;

	if (cmd == NULL)
		return;
	printf("pipe_cmd:\n");
	tmp = cmd->content;
	print_redirect_cmd(tmp);
	print_pipe_cmd(cmd->next);
}

void print_cmd(t_list *cmd)
{
	print_pipe_cmd(cmd);
}


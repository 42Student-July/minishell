/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:54:12 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/22 16:54:23 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handle.h"

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


void print_cmd(const t_cmd *cmd)
{
	printf("\tcmd: %s\n", cmd->cmd);
	print_lists("\targs: ", cmd->args);
	print_files("\tfilenames_in: ", cmd->filenames_in);
	print_files("\tfilenames_out: ", cmd->filenames_out);
}

void print_cmds(t_list *cmd)
{
	const t_cmd *tmp;

	if (cmd == NULL)
		return;
	printf("pipe_cmd:\n");
	tmp = cmd->content;
	print_cmd(tmp);
	print_cmds(cmd->next);
}

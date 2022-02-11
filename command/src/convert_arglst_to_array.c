/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arglst_to_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:37:24 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/11 14:38:20 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

char	**convert_arglst_to_array(t_redirect_cmd *rc)
{
	char	**cmdv;
	// char	*tmp_arg;
	size_t	cmdc;
	size_t	i;
	t_list	*current_arg;

	cmdc = ft_lstsize(rc->cmd->args);
	cmdv = (char **)malloc(sizeof(char) * (cmdc + NULL_CHAR));
	if (cmdv == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	current_arg = rc->cmd->args;
	while (current_arg != NULL)
	{
		// tmp_arg = (char *)current_arg->content;
		// cmdv[i] = ft_strdup(tmp_arg);
		cmdv[i] = (char *)current_arg->content;
		printf("%s\n", cmdv[i]);
		if (cmdv[i] == NULL)
		{
			printf("malloc error\n");
			exit(EXIT_FAILURE);
		}
		i++;
		current_arg = current_arg->next;
	}
	cmdv[i] = NULL;
	// printf("%s\n", cmdv[0]);
	// print_cmdv(cmdv);
	return (cmdv);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arglst_to_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:37:24 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/11 15:25:57 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

char	**convert_arglst_to_array(t_redirect_cmd *rc)
{
	char	**cmdv;
	size_t	cmdc;
	size_t	i;
	t_list	*current_arg;

	cmdc = ft_lstsize(rc->cmd->args);
	cmdv = (char **)malloc(sizeof(char *) * (cmdc + NULL_CHAR));
	if (cmdv == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	current_arg = rc->cmd->args;
	while (current_arg != NULL)
	{
		cmdv[i] = (char *)current_arg->content;
		if (cmdv[i] == NULL)
		{
			printf("malloc error\n");
			exit(EXIT_FAILURE);
		}
		i++;
		current_arg = current_arg->next;
	}
	cmdv[i] = NULL;
	return (cmdv);
}

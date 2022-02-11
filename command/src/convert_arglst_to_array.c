/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmdv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:37:24 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/11 14:01:41 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

char	**convert_arglst_to_array(t_redirect_cmd *rc)
{
	char	**cmdv;
	char	*tmp_arg;
	size_t	cmdc;
	size_t	i;
	t_list	*current_arg;

	//TODO +1用のマクロを作る
	cmdc = ft_lstsize(rc->cmd->args);
	cmdv = (char **)malloc(sizeof(char) * (cmdc + 1));
	if (cmdv == NULL)
		printf("malloc error\n");
	i = 0;
	current_arg = rc->cmd->args;
	while (current_arg != NULL)
	{
		tmp_arg = (char *)current_arg->content;
		cmdv[i] = ft_strdup(tmp_arg);
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
	return (cmdv);
}

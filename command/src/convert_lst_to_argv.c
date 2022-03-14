/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_lst_to_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:51:35 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/15 07:22:20 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "command.h"

char	**convert_lst_to_argv(t_list *args)
{
	char	**cmdv;
	size_t	cmdc;
	size_t	i;
	t_list	*current_arg;

	cmdc = ft_lstsize(args);
	cmdv = (char **)ft_xmalloc(sizeof(char *) * (cmdc + NULL_CHAR));
	i = 0;
	current_arg = args;
	while (current_arg != NULL)
	{
		cmdv[i] = ft_xstrdup(current_arg->content);
		i++;
		current_arg = current_arg->next;
	}
	cmdv[i] = NULL;
	return (cmdv);
}

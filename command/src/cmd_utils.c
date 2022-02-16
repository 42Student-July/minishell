/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:10:49 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/16 16:14:40 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

char	*get_filename(t_cmd *c, int io)
{
	t_file	*file;

	if (io == IN)
		file = c->filenames_in->content;
	else if (io == OUT)
		file = c->filenames_out->content;
	else
		return (NULL);
	return (file->filename);
}

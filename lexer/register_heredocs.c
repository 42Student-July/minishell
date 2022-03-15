/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akito     <akito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:12 by akito             #+#    #+#             */
/*   Updated: 2022/03/15 14:17:12 by akito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "sigaction.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void	write_heredocs(t_lexer *lexer, char *buf, char *delimiter)
{
	char	*filename;

	filename = ft_kvsget(lexer->heredocs, delimiter);
	if (filename == NULL)
		return ;
	write_tmpfile(filename, buf);
}

void	register_heredocs(t_lexer *lexer, char *delimiter)
{
	t_kvs	*kvs;
	char	*tmpfile;

	tmpfile = get_tmpfile_name(ft_itoa(ft_lstsize(lexer->io_here_delimiters)));
	create_tmpfile(tmpfile);
	if (ft_kvsget(lexer->heredocs, delimiter) != NULL)
		exit(EXIT_FAILURE);
	kvs = ft_kvsnew(delimiter, tmpfile);
	free(tmpfile);
	ft_lstadd_back(&lexer->heredocs, ft_lstnew(kvs));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:41:05 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/03 16:41:36 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static bool	can_exit(char *cmd_path)
{
	struct stat	stat_buf;

	if (stat(cmd_path, &stat_buf) == -1)
		exit(EXIT_FAILURE);
	// 所有者の実行許可を確認している
	if ((stat_buf.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	// 所有者の読み込み許可を確認している
	if ((stat_buf.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

void	exec_error(int cp_errno, char *cmd_path)
{
	int	exit_status;

	if (cp_errno == ENOENT)
		exit_status = 127;
	else
		exit_status = 126; // command not found以外は終了ステータスが126
	// errnoがENOEXECでも実行権限がなければEACCESに変更する
	if (cp_errno == ENOEXEC && !can_exit(cmd_path))
		cp_errno = EACCES;
	else if (cp_errno == ENOEXEC)
		exit(EXIT_SUCCESS);
	ft_put_error(strerror(cp_errno), cmd_path);
	exit(exit_status);
}

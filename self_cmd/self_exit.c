/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:33 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/17 17:08:30 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "self_cmd.h"

static int	get_two_complement(long exit_status)
{
	int8_t	two_complement;

	two_complement = exit_status;
	two_complement ^= 0xff;
	two_complement += 1;
	printf("%u\n", (unsigned int)two_complement);
	return (two_complement);
}

bool	is_num(char *str)
{
	size_t	i;

	if (!(str[0] == '+' || str[0] == '-' || ft_isdigit(str[0])))
		return (false);
	i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	exit_success(long exit_status)
{
	printf("start exit_success\n");
	printf("exit_status %ld\n", exit_status);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_status);
}

void	exit_failure(long exit_status, char *error_message)
{
	printf("start exit_failure\n");
	printf("exit_status %ld\n", exit_status);
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(exit_status);
}

char	*make_arg_error_message(char *arg, char *error)
{
	char	*error_message;
	char	*tmp_str;
	char	*tmp_arg;

	if (arg == NULL || error == NULL)
		exit (EXIT_FAILURE);
	tmp_arg = ft_strjoin(arg, ": ");
	if (tmp_arg == NULL)
		exit(EXIT_FAILURE);
	tmp_str = ft_strjoin("minishell: exit: ", tmp_arg);
	if (tmp_str == NULL)
		exit(EXIT_FAILURE);
	free(tmp_arg);
	error_message = ft_strjoin(tmp_str, error);
	if (error_message)
	free(tmp_str);
	return (error_message);
}

char	*make_dfl_error_message(char *error)
{
	char	*error_message;

	if (error == NULL)
		exit(EXIT_FAILURE);
	error_message = ft_strjoin("minishell: exit: ", error);
	if (error_message == NULL)
		exit(EXIT_FAILURE);
	return (error_message);
}

char	*get_arg1(t_cmd *cmd)
{
	char	*arg1;
	t_list	*arg1_lst;

	arg1_lst = cmd->args->next;
	arg1 = arg1_lst->content;
	return (arg1);
}

// この処理は子プロセスでは実行不可
// メッセージは全て標準エラー出力
// エラーのケースは基本255で終了
// 引数が多いかの判定より引数が整数か確認する判定が優先される
// exitされないケースがあるので戻り値の実装は必須
// 引数の正常な範囲はlong int
// 引数の00などは0として捉える
// 引数がマイナスのケースは2の補数を求めて、それをunsigned intとして扱う
// 引数の+-は1つまで
int	exec_self_exit(t_cmd *cmd, t_exec_attr *ea)
{
	long	exit_status;
	int		argc;
	char	*arg1;
	char	*error_message;

	(void)ea;
	argc = ft_lstsize(cmd->args);
	arg1 = get_arg1(cmd);
	if (argc == 1)
		exit_success(EXIT_SUCCESS);
	if (!is_num(arg1) || !ft_atol(arg1, &exit_status))
	{
		error_message = make_arg_error_message(arg1, \
											"numeric argument required");
		exit_failure(255, error_message);
	}
	if (argc > 2)
	{
		// ここにきたらexitしない
		error_message = make_dfl_error_message("too many arguments");
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd(error_message, STDERR_FILENO);
		return (1);
	}
	if (exit_status < 0)
		exit_status = get_two_complement(exit_status);
	if (exit_status > 255)
		exit_success(exit_status % 256);
	else
		exit_success(exit_status);
	return (exit_status);
}

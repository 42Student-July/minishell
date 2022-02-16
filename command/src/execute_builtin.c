/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:07:13 by tkirihar          #+#    #+#             */
/*   Updated: 2022/02/16 14:10:14 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	execute_builtin(t_exec_attr *ea)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		abort_minishell(FORK_ERROR, ea);
	else if (pid == 0)
	{
		if (is_redirect_flag(ea))
			change_direction(ea);
		x_execve(ea);
		exit(0);
	}
	else
	{
		pid = wait(&status);
		if (pid == -1)
			abort_minishell(FORK_ERROR, ea);
	}
}

void	x_execve(t_exec_attr *ea)
{
	// char	**environ;
	
	(void)ea;

	// environ = convert_envlst_to_array(ea);
	// if (execve(ea->command[CMD_NAME], ea->command, environ) == -1)
	// {
	// 	printf("stderror(perror) : %s\n", strerror(errno));
	// 	free(environ);
	// 	exit(EXIT_FAILURE);
	// }
	// free(environ);
}

bool	is_not_exec_path(const char *command)
{
	size_t	i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return (false);
		i++;
	}
	return (true);
}

char	**convert_envlst_to_array(t_exec_attr *ea)
{
	char	**array;
	size_t	env_lst_size;
	size_t	i;
	t_list	*tmp;

	i = 0;
	tmp = ea->env_lst;
	env_lst_size = ft_lstsize(tmp);
	array = (char **)malloc(sizeof(char *) * (env_lst_size + NULL_CHAR));
	if (array == NULL)
		return (NULL);
	while (i < env_lst_size)
	{
		if (ft_kvsget_value(tmp->content) == NULL)
		{
			i++;
			tmp = tmp->next;
			continue ;
		}
		//　TODO: 行数長くなっちゃうからget_keyの引数はlstでもいいのかも
		array[i] = create_environ_line(\
			ft_kvsget_key(tmp->content), ft_kvsget_value(tmp->content), false);
		if (array[i] == NULL)
			abort_minishell_with(MALLOC_ERROR, ea, array);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	// print_array(array);
	return (array);
}


char	*create_environ_line(char *key, char *value, bool is_end)
{
	size_t	key_size;
	size_t	value_size;
	size_t	line_size;
	char	*line;

	key_size = ft_strlen(key);
	value_size = ft_strlen(value);
	line_size = key_size + EQUAL + value_size + LF;
	line = (char *)malloc(sizeof(char) * line_size);
	if (line == NULL)
		return (NULL);
	ft_strlcat(line, key, line_size);
	ft_strlcat(line, "=", line_size);
	ft_strlcat(line, value, line_size);
	if (is_end)
		ft_strlcat(line, "\n", line_size);
	else
		ft_strlcat(line, "\0", line_size);
	return (line);
}

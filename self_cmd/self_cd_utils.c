/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:27:36 by mhirabay          #+#    #+#             */
/*   Updated: 2022/03/04 21:28:25 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "self_cmd.h"

void	update_all_environ(char *new_pwd, t_exec_attr *ea)
{
	char	*export_new_pwd;
	char	*export_pwd;
	char	*pwd;
	t_list	*pwdlst;

	pwdlst = get_lst_by_key(ea->env_lst, "PWD");
	if (pwdlst == NULL)
		// unsetでPWDがなくなったケース
		pwd = ft_strdup("");
	else
	{
		// export PWD= PWDの値を空文字に上書きしたケース
		if (ft_strlen(ft_kvsget_value(pwdlst->content)) == 0)
			pwd = ft_strdup("");
		else
			pwd = ea->current_pwd;
	}
	// free(ea->current_pwd);
	ea->current_pwd = new_pwd;
	export_pwd = create_export_value(pwd);
	export_new_pwd = create_export_value(new_pwd);
	if (pwdlst != NULL)
	{
		update_value(ea->env_lst, "PWD", new_pwd, ea);
		update_value(ea->export_lst, "PWD", export_new_pwd, ea);
	}
	free(new_pwd);
	free(export_new_pwd);
	update_value(ea->env_lst, "OLDPWD", pwd, ea);
	update_value(ea->export_lst, "OLDPWD", export_pwd, ea);
	// free(pwd);
	free(export_pwd);
}

char	*create_new_pwd(char *pwd, char *path)
{
	char	*new_value;
	size_t	new_value_len;
	size_t	path_len;
	size_t	pwd_len;

	pwd_len = ft_strlen(pwd);
	path_len = ft_strlen(path);
	// virtual pathの場合、最後に"/"が入る場合があるため、新しい"/"とかぶってしまう。
	// なので、/を余分に付け加えないようにする
	if (pwd[pwd_len - 1] == '/')
		new_value_len = (pwd_len + path_len + NULL_CHAR);
	else
		new_value_len = (pwd_len + SLASH + path_len + NULL_CHAR);
	new_value = (char *)ft_calloc(sizeof(char), new_value_len);
	if (new_value == NULL)
		return (NULL);
	ft_strlcat(new_value, pwd, new_value_len);
	if (pwd[pwd_len - 1] != '/')
		ft_strlcat(new_value, "/", new_value_len);
	ft_strlcat(new_value, path, new_value_len);
	return (new_value);
}

bool	is_symlink(char *path, t_exec_attr *ea)
{
	struct stat	buf;
	char		*pwd;
	char		*new_pwd;

	pwd = ea->current_pwd;
	new_pwd = create_new_pwd(pwd, path);
	lstat(new_pwd, &buf);
	free(new_pwd);
	return (S_ISLNK(buf.st_mode));
}

bool	is_end_of_slash(char *path)
{
	size_t	i;

	i = 0;
	// slash onlyの場合は対象外とする
	if (ft_strlen(path) == 1)
		return (false);
	while (path[i] != '\0')
		i++;
	if (path[i - 1] == '/')
		return (true);
	return (false);
}

char	*create_str_removed_end(char *path)
{
	size_t	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	path[i - 1] = '\0';
	return (ft_strdup(path));
}

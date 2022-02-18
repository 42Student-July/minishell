#include "lexer.h"
#include "libft.h"

static bool	is_word_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*get_word(char *str)
{
	size_t	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		exit(EXIT_FAILURE); // return argv[i] when $0 ~ $9
	while (is_word_char(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

/*

hoge$HOME"HOGE"

$HOME
-> /home/akky
hoge + /home/akky + "HOGE"
*/

char	*expand_single_envvar(char *str, const char *from, const char *to,
		size_t *i)
{
	char	*replaced_str;
	char	*tmp_front;
	char	*tmp_back;

	tmp_front = ft_substr(str, 0, *i);
	tmp_back = replace_string(&str[*i + 1], from, to);
	*i = ft_strlen(tmp_front);
	if (to != NULL)
		*i += ft_strlen(to);
	replaced_str = ft_strjoin(tmp_front, tmp_back);
	free(tmp_front);
	free(tmp_back);
	return (replaced_str);
}

char	*replace_string(char *str, const char *from, const char *to)
{
	char	*replaced_str;
	char	*tmp;

	replaced_str = ft_strdup(to);
	tmp = ft_strjoin(replaced_str, &str[ft_strlen(from)]);
	free(replaced_str);
	replaced_str = tmp;
	return (replaced_str);
}

void	process_single_envvar(char **str, size_t *i, t_list *env)
{
	char	*env_var;
	char	*tmp;

	env_var = get_word(&((*str)[*i + 1]));
	tmp = expand_single_envvar(*str, env_var, ft_kvsget(env, env_var), i);
	free(*str);
	free(env_var);
	*str = tmp;
}

char	*expand_envvar_str(const char *input, void *env)
{
	char	*str;
	size_t	i;

	str = ft_strdup(input);
	if (str == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0')
			process_single_envvar(&str, &i, env);
		else
			i++;
	}
	return (str);
}

void expand_envvar(void *env)
{
	t_list	*lst;
	char	*tmp;

	lst = env;
	while (lst != NULL)
	{
		tmp = expand_envvar_str(ft_kvsget_value(lst->content), env);
		free(lst->content);
		lst->content = ft_kvsnew(ft_kvsget_key(lst->content), tmp);
		free(tmp);
		lst = lst->next;
	}
}

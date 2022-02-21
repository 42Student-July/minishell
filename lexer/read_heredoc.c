#include "lexer.h"
#include "libft.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <unistd.h>

char	*get_tmpfile_name(char *suffix)
{
	char	*tmp;

	tmp = ft_strjoin("/tmp/minishell-thd-", suffix);
	free(suffix);
	return (tmp);
}

void	write_tmpfile(char *tmpfile, char *buf)
{
	int	fd;
	int	ret;

	if (access("/tmp", F_OK) != 0)
		mkdir("/tmp", 0777);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (buf != NULL)
	{
		ret = write(fd, buf, ft_strlen(buf));
		if (ret == -1)
			exit(EXIT_FAILURE);
	}
	close(fd);
}

void	register_heredocs(t_lexer *lexer, char *buf)
{
	t_kvs	*kvs;
	char	*delimiter;
	t_list	*heredoc_delimiter;
	char	*tmpfile;

	heredoc_delimiter = ft_my_lstpop_front(&lexer->io_here_delimiters);
	delimiter = ft_strdup(heredoc_delimiter->content);
	if (delimiter == NULL)
		exit(EXIT_FAILURE);
	ft_lstdelone(heredoc_delimiter, free);
	tmpfile = get_tmpfile_name(ft_itoa(ft_lstsize(lexer->io_here_delimiters)));
	write_tmpfile(tmpfile, buf);
	free(buf);
	if (ft_kvsget(lexer->heredocs, delimiter) != NULL)
		exit(EXIT_FAILURE);
	kvs = ft_kvsnew(delimiter, tmpfile);
	free(tmpfile);
	ft_lstadd_back(&lexer->heredocs, ft_lstnew(kvs));
}

void	read_heredoc(t_lexer *lexer, t_list *env_list)
{
	char	*buffer;
	char	*tmp;
	char	*line;
	char	**delimiter;
	bool has_quote;

	delimiter = (char **)&(lexer->io_here_delimiters->content);
	buffer = NULL;
	has_quote = ft_strchr(*delimiter, '\'') != NULL || ft_strchr(*delimiter, '"') != NULL;
	if (has_quote)
	{
		tmp = expand_quote_str(*delimiter);
		free(*delimiter);
		*delimiter = tmp;
	}
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strncmp(line, *delimiter, ft_strlen(line)) == 0 &&
			ft_strlen(line) == ft_strlen(*delimiter))
		{
			free(line);
			line = NULL;
			break ;
		}
		tmp = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		buffer = tmp;
		tmp = ft_strjoin(buffer, "\n");
		free(buffer);
		buffer = tmp;
		line = readline("> ");
	}
	if (!has_quote)
	{
		tmp = expand_envvar_str(buffer, env_list);
		free(buffer);
		buffer = tmp;
	}
	register_heredocs(lexer, buffer);
}

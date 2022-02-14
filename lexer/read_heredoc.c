#include "lexer.h"
#include "libft.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <unistd.h>

char	*get_tmpfile_name(t_list **io_delim, char *suffix)
{
	t_list	*heredoc_delimiter;
	char	*tmp;
	char	*tmpfile;

	heredoc_delimiter = ft_my_lstpop_front(io_delim);
	tmpfile = ft_strjoin(heredoc_delimiter->content, suffix);
	ft_lstdelone(heredoc_delimiter, free);
	heredoc_delimiter = NULL;
	free(suffix);
	tmp = ft_strjoin("/tmp/sh-thd-", tmpfile);
	free(tmpfile);
	tmpfile = tmp;
	return (tmpfile);
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
	ret = write(fd, buf, ft_strlen(buf));
	if (ret == -1)
		exit(EXIT_FAILURE);
	close(fd);
}

void	read_heredoc(t_lexer *lexer)
{
	char	*buffer;
	char	*tmp;
	char	*line;
	char	*tmpfile;

	buffer = NULL;
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strncmp(line, (char *)lexer->io_here_delimiters->content,
				ft_strlen(line)) == 0 &&
			ft_strlen(line) == ft_strlen((char *)lexer->io_here_delimiters->content))
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
	tmpfile = get_tmpfile_name(&lexer->io_here_delimiters, ft_itoa(ft_lstsize(lexer->io_here_delimiters)));
	write_tmpfile(tmpfile, buffer);
}

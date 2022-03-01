#include "lexer.h"
#include "libft.h"
#include "sigaction.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <sys/wait.h>
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

void create_tmpfile(char *tmpfile)
{
	int	fd;

	if (access("/tmp", F_OK) != 0)
		mkdir("/tmp", 0777);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		exit(EXIT_FAILURE);
	close(fd);
}

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

bool	read_heredoc(t_lexer *lexer, t_list *env_list)
{
	char	*buffer;
	char	*tmp;
	char	*line;
	t_list *heredoc_delimiter;
	char *delimiter;
	bool	has_quote;
	pid_t	pid;
	pid_t wait_ret;
	int wstatus;

	heredoc_delimiter = ft_my_lstpop_front(&lexer->io_here_delimiters);
	delimiter = ft_strdup(heredoc_delimiter->content);
	ft_lstdelone(heredoc_delimiter, free);
	register_heredocs(lexer, delimiter);
	buffer = NULL;
	has_quote = ft_strchr(delimiter, '\'') != NULL || ft_strchr(delimiter,
			'"') != NULL;
	if (has_quote)
	{
		tmp = expand_quote_str(delimiter);
		free(delimiter);
		delimiter = tmp;
	}
	pid = fork();
	if (pid < 0)
	{
		printf("fork error\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// set_signal_handler_during_heredoc();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		while (line != NULL)
		{
			if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0 &&
				ft_strlen(line) == ft_strlen(delimiter))
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
		write_heredocs(lexer, buffer, delimiter);
		exit(EXIT_SUCCESS);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		while (true)
		{
			wait_ret = waitpid(pid, &wstatus, 0);
			if (wait_ret < 0)
			{
				return (false);
			}
			if (WIFSIGNALED(wstatus))
			{
				printf("\n");
				g_exit_status = WEXITSTATUS(wstatus);
				return (false);
			}
			if (wait_ret > 0)
				break;
			exit(EXIT_FAILURE);
		}
		set_signal_handler_during_command();
	}
	return (true);
}

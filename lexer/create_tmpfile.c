#include "lexer.h"
#include "libft.h"
#include <fcntl.h>
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

void	create_tmpfile(char *tmpfile)
{
	int	fd;

	if (access("/tmp", F_OK) != 0)
		mkdir("/tmp", 0777);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		exit(EXIT_FAILURE);
	close(fd);
}

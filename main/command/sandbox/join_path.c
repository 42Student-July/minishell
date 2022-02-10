#include "../includes/command.h"

void	execute_command(char *const *command, char *const *environ)
{
	// TODO: NULL判定などは未実装
	if (execve(command[0], command, environ) == -1)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

// void	join_path(const char **argv, char **command)
// {
// 	size_t	path_len;
// 	size_t	file_len;
// 	size_t	file_path_len;
// 	char	*bin_path;
// 	char	*exec_command;

// 	path_len = ft_strlen(*argv);
// 	file_len = ft_strlen("/bin/");
// 	file_path_len = path_len + file_len;
// 	// *command = (char *)malloc(sizeof(char) * file_path_len + 1);
// 	// ft_strlcat(*command, "/bin/", path_len);
// 	// ft_strlcat(*command, *argv, file_len);
// 	exec_command = ft_strjoin(bin_path, *command);
// 	printf("%s\n", *command);
// }

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

char *const	*create_command(int argc, const char *argv[])
{
	int		i;
	char	*bin_path;

	i = 0;
	char **command;
	bin_path = "/bin/";
	// argv[0]は実行コマンドなんで、なくす。
	// 最後のNULL止めのために+1する。
	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	if (is_not_exec_path(argv[1]))
	{
		command[i] = ft_strjoin(bin_path, argv[1]);
		i++;
	}
	while (i < argc - 1)
	{
		command[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	return (command);
}


int	main(int argc, const char *argv[])
{
	char		**environ;
	char *const	*command;
	int			command_num;

	command_num = argc;
	command = create_command(command_num, argv);
	// 第1引数 PATH, 第2引数 コマンド名＋実行引数
	execute_command(command, environ);
	return (0);
}

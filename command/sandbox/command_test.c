
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
	char	**command;

	i = 0;
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

static void	print_cwd(void)
{
    char pathname[BUFSIZ] = {"\0"};

}

void	x_chdir(const char *path)
{
	if (chdir(path) == -1)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	print_cwd();
}

void	my_cd(const char **command, char **environ)
{
	(void)environ;
	x_chdir(command[2]);
}

void	x_getcwd(char *pathname, int bufsiz)
{
	if (getcwd(pathname, bufsiz) == NULL)
	{
		printf("stderror(perror) : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	my_pwd(const char **command, char **environ)
{
	char	pathname[BUFSIZ];

	(void)environ;
	x_getcwd(pathname, BUFSIZ);
	printf("%s\n", pathname);
}

// echo などの自作コマンドを実行する関数
bool	execute_my_command(const char **command, char **environ)
{
	(void)environ;
	if (ft_strncmp(command[1], CD, ft_strlen(CD)) == 0)
		my_cd(command, environ);
	if (ft_strncmp(command[1], PWD, ft_strlen(PWD)) == 0)
		my_pwd(command, environ);
	my_pwd(command, environ);
	return (true);
}

bool	is_my_command(const char *c)
{
	size_t c_len;

	c_len = ft_strlen(c);
	if (
		ft_strncmp(c, CD, c_len) &&
		ft_strncmp(c, ECHO, c_len) &&
		ft_strncmp(c, PWD, c_len) &&
		ft_strncmp(c, EXIT, c_len)
		)
		return (false);
	return (true);
}

void	hoge_fork(char *const *command, char **environ)
{
	pid_t	pid;
	int		status;
	pid_t	error_num;

	pid = fork();
	if (pid == -1)
	{
		printf("Error\n");
		exit(1);
	}
	else if (pid == 0)
	{
		printf("ch\n");
		execute_command(command, environ);
	}
	else
	{
		printf("parent\n");
		error_num = wait(&status);
		if (pid == -1)
		{
			printf("Error\n");
			exit(1);
		}
	}
}

int	main(int argc, const char *argv[])
{
	char		**environ;
	char *const	*command;
	int			command_num;

	environ = NULL;
	command_num = argc;
	// argvの引数は修正が必要そう
	if (is_my_command(argv[1]))
		execute_my_command(argv, environ);
	else
	{
		command = create_command(command_num, argv);
		hoge_fork(command, environ);
	}
	// 第1引数 PATH, 第2引数 コマンド名＋実行引数
	return (0);
}


#include "../includes/command.h"

char *const	*create_command(int argc, const char *argv[])
{
	int	i;

	i = 0;
	char **command;
	command = (char **)malloc(sizeof(char *) * (argc - 1 + 1));
	while (i < argc - 1)
	{
		command[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	return (command);
}

bool	execute_my_command()
{

}



bool	is_my_command(char *const *c, int c_num)
{
	int	i;
	char *my_command[MY_COMMAND_NUM];

	if (	c[NAME] == CD ||
			c[NAME] == ECHO ||
			c[NAME] == PWD ||
			c[NAME] == EXIT
		)
		return (true);
	return (false);
}

int	main(int argc, const char *argv[])
{
	char		**environ;
	char *const	*command;
	int			command_num;

	command_num = argc;
	command = create_command(command_num, argv);

	if (is_my_command)
		execute_my_command(command, environ);
	// 第1引数 PATH, 第2引数 コマンド名＋実行引数
	execute_command(command, environ);
	return (0);
}

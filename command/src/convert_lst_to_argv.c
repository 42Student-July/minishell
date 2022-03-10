
#include "command.h"

char	**convert_lst_to_argv(t_list *args)
{
	char	**cmdv;
	size_t	cmdc;
	size_t	i;
	t_list	*current_arg;

	cmdc = ft_lstsize(args);
	cmdv = (char **)malloc(sizeof(char *) * (cmdc + NULL_CHAR));
	if (cmdv == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	current_arg = args;
	while (current_arg != NULL)
	{
		cmdv[i] = ft_strdup(current_arg->content);
		if (cmdv[i] == NULL)
		{
			printf("malloc error\n");
			exit(EXIT_FAILURE);
		}
		i++;
		current_arg = current_arg->next;
	}
	cmdv[i] = NULL;
	return (cmdv);
}

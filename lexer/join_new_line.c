#include "common.h"
#include "lexer.h"
#include "libft.h"
#include <readline/readline.h>

void join_new_line(t_lexer *lexer)
{
	char *line;
	char *tmp;

	tmp = ft_strjoin(lexer->input, "\n");
	free(lexer->input);
	lexer->input = tmp;
	line = readline("");
	ft_putendl_fd("", STDOUT);
	if (line == NULL)
		return ;
	tmp = ft_strjoin(lexer->input, line);
	free(lexer->input);
	free(line);
	lexer->input = tmp;
}


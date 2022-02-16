#include "lexer.h"
#include "libft.h"

void	add_heredoc_delimiter(t_lexer *lexer)
{
	char	*delimiter;
	size_t pos;
	size_t pos_tail;

	read_char(lexer);
	pos = lexer->position;
	pos_tail = pos;
	while (!ft_isspace(lexer->input[pos_tail]) && lexer->input[pos_tail] != '\0')
	{
		if (is_forbidden_char(lexer->input[pos_tail]))
			exit(EXIT_FAILURE);
		pos_tail++;
	}
	delimiter = ft_substr(lexer->input, pos, pos_tail - pos);
	ft_lstadd_back(&lexer->io_here_delimiters, ft_lstnew(delimiter));
}

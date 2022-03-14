#include "lexer.h"
#include "libft.h"

bool	add_heredoc_delimiter(t_lexer *lexer)
{
	char	*delimiter;
	size_t	pos;
	size_t	pos_tail;

	read_char(lexer);
	if (lexer->skip_whitespace)
		skip_whitespace(lexer);
	pos = lexer->position;
	pos_tail = pos;
	while (!ft_isspace(lexer->input[pos_tail])
		&& lexer->input[pos_tail] != '\0')
		pos_tail++;
	delimiter = ft_substr(lexer->input, pos, pos_tail - pos);
	if (*delimiter == '\0' || ft_strchr(delimiter, '\'')
		|| ft_strchr(delimiter, '"') || ft_strchr(delimiter, '|'))
	{
		free(delimiter);
		return (false);
	}
	ft_lstadd_back(&lexer->io_here_delimiters, ft_lstnew(delimiter));
	return (true);
}

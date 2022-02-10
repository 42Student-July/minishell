#include "parser.h"
#include "libft.h"
#include "lexer.h"
#include <stdbool.h>

t_file *new_file(t_token *token, bool is_append)
{
	t_file *file;

	file = (t_file *)ft_calloc(sizeof(t_file), 1);
	if (file == NULL)
		exit(EXIT_FAILURE);
	file->filename = get_literal(token);
	if (file->filename == NULL)
		exit(EXIT_FAILURE);
	file->is_append = is_append;
	return (file);
}


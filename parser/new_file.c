#include "parser.h"
#include "libft.h"
#include "lexer.h"
#include <stdbool.h>

t_file *new_file(char *filename, bool is_double)
{
	t_file *file;

	file = (t_file *)ft_calloc(sizeof(t_file), 1);
	if (file == NULL)
		exit(EXIT_FAILURE);
	file->filename = filename;
	if (file->filename == NULL)
		exit(EXIT_FAILURE);
	file->is_double = is_double;
	return (file);
}


#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include <stdbool.h>

t_file	*new_file(char *filename, bool is_double)
{
	t_file	*file;

	file = (t_file *)ft_calloc(sizeof(t_file), 1);
	if (file == NULL)
		exit(EXIT_FAILURE);
	if (filename != NULL)
	{
		file->filename = ft_strdup(filename);
		if (file->filename == NULL)
			exit(EXIT_FAILURE);
	}
	else
		file->filename = NULL;
	file->is_double = is_double;
	return (file);
}

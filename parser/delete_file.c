#include "parser.h"
#include "libft.h"
#include "lexer.h"
#include <stdbool.h>

void delete_file(void *file_ptr)
{
	t_file *file;

	file = (t_file *)file_ptr;
	free(file->filename);
	file->filename = NULL;
	free(file);
}

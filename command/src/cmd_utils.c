
#include "command.h"

char	*get_filename(t_cmd *c, int io)
{
	t_file	*file;

	if (io == IN)
		file = c->filenames_in->content;
	else if (io == OUT)
		file = c->filenames_out->content;
	else
		return (NULL);
	return (file->filename);
}

bool	is_dir(char *cmd_path)
{
	DIR	*dir;

	dir = opendir(cmd_path);
	if (dir)
		return (true);
	return (false);
}

bool	*malloc_has_not_permission(size_t size)
{
	bool	*ret;

	ret = (bool *)malloc(sizeof(bool) * size);
	if (ret == NULL)
		exit(EXIT_FAILURE);
	return (ret);
}

#include "libft.h"

void	join_line_to_buffer(char **buffer, char **line)
{
	char	*tmp;

	tmp = ft_strjoin(*buffer, *line);
	free(*buffer);
	free(*line);
	*line = NULL;
	*buffer = tmp;
	tmp = ft_strjoin(*buffer, "\n");
	free(*buffer);
	*buffer = tmp;
}

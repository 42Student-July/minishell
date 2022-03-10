
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define FD_SIZE 65536
# define BUFFER_SIZE 4096

size_t	ft_gnl_strlen(const char *str);
char	*ft_gnl_substr(char const *s, unsigned int start, size_t len);
char	*ft_gnl_strjoin(char const *s1, char const *s2);
char	*ft_gnl_strdup(const char *s);
char	*ft_gnl_strchr(const char *s, int c);
size_t	ft_gnl_strlcpy(char *dst, const char *src, size_t size);
char	*get_next_line(int fd);
#endif

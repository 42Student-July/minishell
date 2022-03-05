/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:14:14 by akito             #+#    #+#             */
/*   Updated: 2022/03/05 22:36:48 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_kvs
{
	char	*key;
	char	*value;
}	t_kvs;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_iscap_alpha(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_isspace(int c);
int		ft_isletter(int c);
char	*ft_strcut_back(char *str, char c);

// extra files

int64_t	ft_my_putchar(char c);
int64_t	ft_my_putstr(const char *s);
int64_t	ft_my_putnbr(int n);
int64_t	ft_my_unsigned_putnbr(unsigned int n);
int64_t	ft_my_putbase(size_t n, char *base);
int64_t	ft_my_putpointer(size_t n);
double	ft_my_atof(const char *nptr);
char	*ft_kvsget_key(void *content);
char	*ft_kvsget_value(void *content);
void	*ft_kvsnew(char *key, char *value);
char	*ft_kvsget(t_list *list, char *key);
bool	ft_streq(char *a, char *b);
void	ft_kvsdelete(void *elm);
void	ft_kvsreplace_value(void *content, char *new_value);
void	ft_put_error(char *message);
void	ft_put_cmd_error(char *cmd, char *message);
void	ft_put_arg_error(char *cmd, char *arg, char *message);
bool	ft_atol(const char *nptr, long *num);
char	*ft_replace_str(const char *src, const char *target, \
						const char *replace);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new_elm);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
bool	ft_lstadd_back(t_list **lst, t_list *new_elm);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
bool	ft_lstdel(t_list *lst, t_list *target);
t_list	*ft_my_lstpop_front(t_list **lst);
void 	ft_lstiter_with_var(t_list *lst, void (*f)(void *, void *), void *var);


#endif

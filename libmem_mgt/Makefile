NAME = 		libmem_mgt.a

SRCS = 		mem_mgt_malloc.c \
			mem_mgt_free.c \
			mem_mgt_finish_check.c \
			mem_mgt_check.c \
			mem_mgt_free_all.c

OBJS = 		$(SRCS:.c=.o)

CC =		gcc

RM =		rm -f

CFLAGS =	-Wall -Wextra -Werror

$(NAME):	$(OBJS)
			ar rcs $@ $^

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

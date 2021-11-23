SRCS	= pipex.c pipex_utils.c
OBJS	= ${SRCS:.c=.o}

CC	= cc

CFLAGS = -Wall -Werror -Wextra

NAME	= pipex

.c.o:
	make -C ./libft all
	${CC} ${CFLAGS} -c ${SRCS}

RM	= rm -f

$(NAME):	${OBJS}
	cc -o $(NAME) ${OBJS} -L./libft -lft


all:	$(NAME)

clean:
	${RM} ${OBJS}
	make -C ./libft clean

fclean:	clean
	${RM} ${NAME}
	make -C ./libft fclean

re:	fclean all

.PHONY: 	all clean fclean

SRCLIST	= pipe_factory.c process_factory.c pathname.c pipex_utils.c \
		  pipex_init.c heredoc.c pipex.c

SRCDIR	= ./

SRCS	= ${addprefix ${SRCDIR}, ${SRCLIST}}

OBJS	= ${SRCS:.c=.o}

INCS	= -iquote libft

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

NAME	= pipex

MAKE	= make

LIBFT	= libft/libft.a

all:	${NAME}

bonus:	${NAME}

.c.o:
	${CC} ${CFLAGS} ${INCS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${INCS} -o ${NAME} ${OBJS} ${LIBFT}

${LIBFT}:
	${MAKE} -C libft

clean:
	${RM} ${OBJS}
	${MAKE} -C libft clean

fclean: clean
	${RM} ${NAME}
	${MAKE} -C libft fclean

re:	fclean all

.PHONY:	all clean fclean re

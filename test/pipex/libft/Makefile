SRCLIST	= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	  ft_toupper.c ft_tolower.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	  ft_memmove.c ft_memset.c ft_calloc.c ft_bzero.c ft_strchr.c \
	  ft_strlen.c ft_strrchr.c ft_strdup.c ft_strncmp.c ft_strnstr.c \
	  ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_isinteger.c ft_substr.c \
	  ft_strjoin.c ft_strtrim.c ft_split.c ft_split_utils.c ft_itoa.c \
	  ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putendl_fd.c \
	  ft_putnbr_fd.c ft_putstr_fd.c ft_lstnew.c ft_lstadd_front.c \
	  ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
	  ft_lstiter.c ft_lstmap.c ft_printf.c ft_printf_write.c \
	  ft_printf_write_extra.c get_next_line.c ft_split_utils2.c

SRCDIR	= ./

SRCS	= ${addprefix ${SRCDIR}, ${SRCLIST}}

OBJS	= ${SRCS:.c=.o}

INCDIR	= ./

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

NAME	= libft.a

.c.o:
	${CC} ${CFLAGS} -I${INCDIR} -c $< -o ${<:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
	ar crs ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re

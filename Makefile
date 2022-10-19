# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 15:41:04 by tliangso          #+#    #+#              #
#    Updated: 2022/10/19 13:08:32 by tliangso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME		= minishell
BONUS_NAME	=

### DIR ###
HEAD			= ./
DIRSRC			= ./
EXECUTOR_SRC	= executor/
LEXER_SRC		= lexer/
PARSER_SRC		= parser/
EXPANDER_SRC	= expander/
LIBFT_SRC		= libft/
OBJ_SRC			= objs/

### TESTER GIT URL ###
TESTER1		=
TESTER2		=
TESTER3		=
TESTER4		=

### SOURCE FILE ###
SRC		=	minishell.c

LEXER	= lexer.c

PARSER	= parser.c

EXPANDER = expander.c

EXECUTOR = executor.c

LIBFT	= libft.c

### PATH ###
SRCS		= ${addprefix ${DIRSRC}, ${SRC}}
LEXER_SRCS	= ${addprefix ${LEXER_SRC}, ${LEXER}}
PARSER_SRCS	= ${addprefix ${PARSER_SRC}, ${PARSER}}
EXPANDER_SRCS	= ${addprefix ${EXPANDER_SRC}, ${EXPANDER}}
EXECUTOR_SRCS	= ${addprefix ${EXECUTOR_SRC}, ${EXECUTOR}}
LIBFT_SRCS	= ${addprefix ${LIBFT_SRC}, ${LIBFT}}

### OBJECT FILE ###
OBJS		= $(SRCS:.c=.o)
LEXER_OBJS	= $(LEXER_SRCS:.c=.o)
PARSER_OBJS	= $(PARSER_SRCS:.c=.o)
EXPANDER_OBJS	= $(EXPANDER_SRCS:.c=.o)
EXECUTOR_OBJS	= $(EXECUTOR_SRCS:.c=.o)
LIBFT_OBJS	= $(LIBFT_SRCS:.c=.o)

### COMPILATION ###
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g
LIBFLAGS = -L/usr/lib -I/usr/include -I${HEAD} -lreadline

### COLORS ###
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### RULES ###

.c.o:
	@${CC} ${CFLAGS} -c ${LIBFLAGS} $< -o ${<:.c=.o}
	@echo "$(BLUE)${CC} $(WHITE)$(notdir $@)$(NOC)"

all: ${NAME}

# $(OBJ_SRC)%.o: $(DIRSRC)%.c $(HEAD)$(NAME).h
# 	@mkdir -p objs
# 	@${CC} ${CFLAGS} -I${HEAD} -c -o $@ $<
# 	@echo "$(BLUE)$(CC) $(WHITE)$(notdir $@)$(NOC)"

bonus: ${BONUS_NAME}

${NAME}:	${OBJS} ${LIBFT_OBJS} ${PARSER_OBJS} ${LEXER_OBJS} ${EXPANDER_OBJS} ${EXECUTOR_OBJS}

	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT_OBJS} ${PARSER_OBJS} ${LEXER_OBJS} ${EXPANDER_OBJS} ${EXECUTOR_OBJS}
	@echo "$(GREEN)$@$(NOC)"

${BONUS_NAME}:		${BONUS_OBJS} ${LIBFT_OBJS} ${SHARE_OBJS}
	@${CC} ${CFLAGS} -o ${BONUS_NAME} ${BONUS_OBJS} ${LIBFT_OBJS} ${SHARE_OBJS}
	@echo "$(GREEN)${BONUS_NAME}$(NOC)"

extra:	${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS} ${LIBFT_OBJS}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS} ${LIBFT_OBJS}

clean:
	@echo "$(RED)clean$(NOC)"
	@${RM} ${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS} ${LIBFT_OBJS} ${PARSER_OBJS} ${LEXER_OBJS} ${EXPANDER_OBJS} ${EXECUTOR_OBJS}

fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@${RM} ${NAME} ${BONUS_NAME}

re: fclean	all

tester:
	@echo "$(YELLOW)Testers are not perfect but its good enough$(NOC)"
	git clone ${TESTER1} TESTER1
	git clone ${TESTER2} TESTER2
	git clone ${TESTER3} TESTER3
	git clone ${TESTER3} TESTER4

norm:
	norminette

gitpush:
	git add .
	git status
	git commit -m ${NAME}
	git push

help:
	@clear
	@echo "$(GREEN)Avaibles options:$(NOC)"
	@echo "$(RED)==================$(NOC)"
	@echo "$(RED)| $(YELLOW)make ${NAME} $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make ${BONUS_NAME}   $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make norm      $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make tester    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make clean     $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make fclean    $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make re        $(RED)|$(NOC)"
	@echo "$(RED)| $(YELLOW)make help      $(RED)|$(NOC)"
	@echo "$(RED)==================$(NOC)"

tar:
	tar -zcvf ${NAME}.tar.gz *

.PHONY:		all	clean	fclean	re bonus norm gitpush tester help tar

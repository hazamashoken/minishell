# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 15:41:04 by tliangso          #+#    #+#              #
#    Updated: 2022/10/19 19:46:09 by tliangso         ###   ########.fr        #
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
OBJ_DIR			= objs/

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
SRCS		= ${addprefix ${DIRSRC}, ${SRC}} \
	${addprefix ${LEXER_SRC}, ${LEXER}} \
	${addprefix ${PARSER_SRC}, ${PARSER}} \
	${addprefix ${EXPANDER_SRC}, ${EXPANDER}} \
	${addprefix ${EXECUTOR_SRC}, ${EXECUTOR}} \
	${addprefix ${LIBFT_SRC}, ${LIBFT}}

### OBJECT FILE ###
OBJS		= $(SRCS:.c=.o)


### COMPILATION ###
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g
LIBFLAGS = -I${HEAD} -lreadline

### COLORS ###
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### RULES ###

all: ${NAME}

# $(OBJS): %.o: $(DIRSRC)%.c
# 	@mkdir -p objs
# 	@${CC} ${CFLAGS} ${LIBFLAGS} -o $@ $<
# 	@echo "$(BLUE)$(CC) $(WHITE)$(notdir $@)$(NOC)"

bonus: ${BONUS_NAME}

test_p:
	echo ${SRCS}

%.o: %.c
	@mkdir -p objs
	@${CC} ${CFLAGS} ${LIBFLAGS} -c $< -o ${<:.c=.o}
	@echo "$(BLUE)${CC} $(WHITE)$(notdir $@)$(NOC)"

${NAME}:	${OBJS}

	@${CC} ${OBJS} ${LIBFLAGS} ${CFLAGS} -o ${NAME}
	@echo "$(GREEN)$@$(NOC)"

clean:
	@echo "$(RED)clean$(NOC)"
	@${RM} ${OBJS}

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

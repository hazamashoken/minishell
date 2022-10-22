# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 15:41:04 by tliangso          #+#    #+#              #
#    Updated: 2022/10/22 13:50:05 by tliangso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME		= minishell
LEXER_NAME	= lexer

### DIR ###
HEAD			= -I./includes
DIRSRC			= ./
BUILD_DIR		= ./build
LEXER_DIR		= ./src/lexer
LIBFT_DIR		= ./src/libft

### TESTER GIT URL ###
TESTER1		=
TESTER2		=
TESTER3		=
TESTER4		=

### PATH ###
SRCS		= $(shell find $(DIRSRC) -name '*.c')
LEXER_SRCS		= $(shell find $(LEXER_DIR) -name '*.c') $(shell find $(LIBFT_DIR) -name '*.c')

### OBJECT FILE ###
OBJS		= $(SRCS:%=$(BUILD_DIR)/%.o)
LEXER_OBJS		= $(LEXER_SRCS:%=$(BUILD_DIR)/%.o)

### INCLUDE ###
LIB 	= $(HEAD) -lreadline

### COMPILATION ###
CC		= gcc
RM		= rm -r
CFLAGS	= -Wall -Wextra -Werror -g

### COLORS ###
NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

### RULES ###
lexer: $(BUILD_DIR)/$(LEXER_NAME)

all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(NAME): $(OBJS)
	@${CC} ${CFLAGS} $(OBJS) $(LIB) -o $@
	@echo "$(GREEN)$@$(NOC)"

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LIB) -c -o $@ $<
	@echo "$(GREEN)gcc $@$(NOC)"

$(BUILD_DIR)/$(LEXER_NAME): $(LEXER_OBJS)
	@${CC} ${CFLAGS} $(LEXER_OBJS) $(LIB) -o $@
	@echo "$(GREEN)$@$(NOC)"

test:
	@echo "$(LIB)\n"
	@echo "$(SRCS)\n"
	@echo "$(BUILD_DIR)/$(NAME)\n"
	@echo "$(OBJS)\n"

bonus: ${BONUS_NAME}

clean:
	@echo "$(RED)clean$(NOC)"
	@${RM} $(BUILD_DIR)

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

.PHONY:		all	clean	fclean	re bonus norm gitpush tester help tar test lexer

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 15:41:04 by tliangso          #+#    #+#              #
#    Updated: 2022/10/24 15:08:44 by tliangso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME		= minishell
LEXER_NAME	= lexer.out
PROTO_NAME	= prototype.out

### DIR ###
HEAD			= -I./includes
DIRSRC			= ./src
BUILD_DIR		= ./build
LEXER_DIR		= ./src/lexer
PROTO_DIR		= ./prototype
LIBFT_DIR		= ./src/libft

### TESTER GIT URL ###
TESTER1		=
TESTER2		=
TESTER3		=
TESTER4		=

### PATH ###
SRCS		= $(shell find $(DIRSRC) -name '*.c')
PROTO_SRCS	= $(shell find $(PROTO_DIR) -name '*.c') $(shell find $(LIBFT_DIR) -name '*.c')
LEXER_SRCS		= $(shell find $(LEXER_DIR) -name '*.c') $(shell find $(LIBFT_DIR) -name '*.c')

### OBJECT FILE ###
OBJS		= $(SRCS:%=$(BUILD_DIR)/%.o)
PROTO_OBJS		= $(PROTO_SRCS:%=$(BUILD_DIR)/%.o)
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

$(BUILD_DIR)/$(LEXER_NAME): $(LEXER_OBJS)
	@${CC} ${CFLAGS} $(LEXER_OBJS) $(LIB) -o $@
	@echo "$(GREEN)$@$(NOC)"

all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(PROTO_NAME): $(PROTO_OBJS)
	@${CC} ${CFLAGS} $(PROTO_OBJS) $(LIB) -o $@
	@echo "$(GREEN)$@$(NOC)"

$(BUILD_DIR)/$(NAME): $(OBJS)
	@${CC} ${CFLAGS} $(OBJS) $(LIB) -o $@
	@echo "$(GREEN)$@$(NOC)"

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LIB) -c -o $@ $<
	@echo "$(GREEN)gcc $@$(NOC)"

test:
	@echo "$(LIB)\n"
	@echo "$(LEXER_SRCS)\n"
	@echo "$(BUILD_DIR)/$(LEXER_NAME)\n"
	@echo "$(LEXER_OBJS)\n"

bonus: ${BONUS_NAME}

clean:
	@echo "$(RED)clean$(NOC)"
	@if [ -f $(BUILD_DIR)/$(LEXER_NAME) ]; then\
		mv $(BUILD_DIR)/$(LEXER_NAME) .;\
	fi
	@if [ -d $(BUILD_DIR) ]; then\
		${RM} $(BUILD_DIR);\
	fi

fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@if [ -f ${NAME} ]; then\
		${RM} ${NAME};\
	fi
	@if [ -f ${LEXER_NAME} ]; then\
		${RM} ${LEXER_NAME};\
	fi

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

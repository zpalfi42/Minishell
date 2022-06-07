# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zpalfi <zpalfi@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 13:15:04 by zpalfi            #+#    #+#              #
#    Updated: 2022/03/14 13:28:44 by zpalfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= get_next_line

INCLUDE_DIR	= include
SRC_DIR		= src
OBJ_DIR		= obj
OUTPUT		= $(NAME).a

INC			= -I $(INCLUDE_DIR)

SRC			= get_next_line.c \
			  get_next_line_utils.c \

OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g $(INC)

obj/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^

all: $(NAME)

$(NAME): $(OBJ)
	@ar -cr $(OUTPUT) $(OBJ)

clean:
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@rm -rf $(OUTPUT)

re:	fclean all

.PHONY: all re fclean clean

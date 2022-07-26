# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 13:15:04 by zpalfi            #+#    #+#              #
#    Updated: 2022/07/26 17:27:18 by zpalfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= get_next_line

INCLUDE_DIR	= include
SRC_DIR		= src
OBJ_DIR		= obj
OUTPUT		= $(NAME).a

INC			= -I $(INCLUDE_DIR)

SRC			= src/get_next_line.c \
			  src/get_next_line_utils.c \

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g $(INC)

OBJ		= $(SRC:%.c=%.o)
CFLAGS	= -Wall -Wextra -Werror -I include
CC		= gcc

$(NAME): $(OBJ) include/get_next_line.h
	@ar rc $(NAME) $(OBJ)

.PHONY : clean
clean:
	@rm -f *.o

.PHONY : fclean
fclean: clean
	@rm -f $(NAME)

.PHONY : all
all: $(NAME)

.PHONY : re
re: fclean all

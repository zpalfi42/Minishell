# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 14:18:26 by zpalfi            #+#    #+#              #
#    Updated: 2022/03/14 13:52:54 by zpalfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft
OUTPUT		= $(NAME).a

#------------- DIRS -------------#

INCLUDE_DIR	= include
SRC_DIR		= src
OBJ_DIR		= obj

#------------- FILES --------------#

INC			= -I $(INCLUDE_DIR)
SRC 		= $(shell ls $(SRC_DIR) | grep -E "ft_.+\.c") \

OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

#--------------- COMPILATION ---------------#

CFLAGS		= -Wall -Werror -Wextra -g $(INC)
CC			= gcc

obj/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^

all: $(NAME)

$(NAME): $(OBJ)
	@ar -cr $(OUTPUT) $(OBJ)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(OUTPUT)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 12:16:53 by zpalfi            #+#    #+#              #
#    Updated: 2022/06/01 15:33:00 by zpalfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

#--------------- DIRS ---------------#

INCLUDE_DIR	= include
SRC_DIR		= src
LIBS_DIR	= libs
OBJS_DIR	= objs

#--------------- FILES ---------------#

LIBS			= $(LIBS_DIR)/Libft/libft.a \

LIBS_HEADERS	= -I $(LIBS_DIR)/Libft/include/ \

INC				= -I $(INCLUDE_DIR) $(LIBS_HEADERS)

SRC				= main.c \
				  count_words.c \
				  save_tokens.c \
				  print_miniconcha.c \

OBJ				= $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

#--------------- COMPILATION ---------------#

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g $(INC) -I ~/.brew/opt/readline/include

#--------------- RULES ---------------#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "Compiling $^"

all:	$(NAME)

$(NAME): $(OBJ) $(LIBS)
	@$(CC) $(OBJ) -lreadline -L ~/.brew/opt/readline/lib $(LIBS) -o $(NAME)
	@echo "Built $(NAME)"

$(LIBS_DIR)/Libft/libft.a:
	@make -C $(LIBS_DIR)/Libft

clean:
	@rm -rf $(OBJS_DIR)

fclean:	clean
	@make fclean -C $(LIBS_DIR)/Libft
	@rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean
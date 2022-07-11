# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 12:16:53 by zpalfi            #+#    #+#              #
#    Updated: 2022/07/11 17:31:25 by zpalfi           ###   ########.fr        #
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
				  $(LIBS_DIR)/Get_Next_Line/get_next_line.a \

LIBS_HEADERS	= -I $(LIBS_DIR)/Libft/include/ \
				  -I $(LIBS_DIR)/Get_Next_Line/include/ \

INC				= -I $(INCLUDE_DIR) $(LIBS_HEADERS)

SRC				=	cd.c \
					ast.c \
					pwd.c \
					env.c \
					exit.c \
					main.c \
					free.c \
					echo.c \
					unset.c \
					utils.c \
					error.c \
					parser.c \
					signal.c \
					export.c \
					lst_new.c \
					do_other.c \
					init_env.c \
					path_cmd.c \
					cd_utils.c \
					token_len.c \
					in_out_file.c \
					pipe_parser.c \
					save_tokens.c \
					export_utils.c \
					cmd_add_back.c \
					count_tokens.c \
					files_add_back.c \
					export_utils_2.c \
					token_len_utils.c \
					print_miniconcha.c \
					save_tokens_utils.c \

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

$(LIBS_DIR)/Get_Next_Line/get_next_line.a:
	@make -C $(LIBS_DIR)/Get_Next_Line

clean:
	@rm -rf $(OBJS_DIR)

fclean:	clean
	@make fclean -C $(LIBS_DIR)/Libft
	@make fclean -C $(LIBS_DIR)/Get_Next_Line
	@rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 12:16:53 by zpalfi            #+#    #+#              #
#    Updated: 2022/09/19 15:37:32 by zpalfi           ###   ########.fr        #
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
					exec.c \
					main.c \
					free.c \
					echo.c \
					unset.c \
					utils.c \
					error.c \
					parser.c \
					signal.c \
					export.c \
					in_file.c \
					files_lst_heredoc.c \
					do_dir.c \
					out_file.c \
					do_other.c \
					init_env.c \
					path_cmd.c \
					cd_utils.c \
					token_len.c \
					assign_io.c \
					cd_utils_2.c\
					pipe_parser.c \
					save_tokens.c \
					cmd_lst_new.c \
					export_utils.c \
					cmd_add_back.c \
					count_tokens.c \
					files_lst_new.c \
					exec_simple.c \
					files_add_back.c \
					export_utils_2.c \
					token_len_utils.c \
					print_miniconcha.c \
					save_tokens_init.c \
					save_tokens_utils.c \
					find_cmd_after_redir.c \

OBJ				= $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

#--------------- COMPILATION ---------------#

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g $(INC) -I ~/.brew/opt/readline/include

#--------------- RULES ---------------#

objs/%.o: src/%.c ./include/minishell.h
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $<
	@echo "Compiling $^"

all:	$(NAME)

$(NAME): $(OBJ) $(LIBS) ./include/minishell.h
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -L ~/.brew/opt/readline/lib $(LIBS) -o $(NAME)
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

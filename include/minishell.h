/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:10:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 13:40:32 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <term.h>
# include <fcntl.h>
# include <errno.h>
# include <curses.h>
# include <dirent.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_data
{
	int		dc;
	int		sc;
	int		dc_2;
	int		sc_2;
	char	**tokens;
	char	*line;
	int		count;
	int		word;
	int		len;
	int		i;
	t_list	*env;
}	t_data;

typedef struct s_ast
{
	char	*cmd;
	int		nr;
	int		np;
	char	*opt;
	char	*arg;
	char	*home;
	char	*dir;
}	t_ast;

int		sig_handler(void);
int		is_valid_name(char c);
int		valid_export(t_data *data);
int		ft_strcmp(char *s, char *d);
int		export_exists(t_data *data);
int		save_env(t_data *data, int j);
int		token_len(t_data *data, int i);
int		save_env_2(t_data *data, int j, char *name);

void	ast(t_data *data);
void	parser(t_data *data);
void	free_all(t_data *data);
void	print_miniconcha(void);
void	save_tokens(t_data *data);
void	change_value(t_data *data);
void	count_tokens(t_data *data);
void	do_cd(t_data *data, t_ast *ast);
void	do_env(t_data *data, t_ast *ast);
void	do_pwd(t_data *data, t_ast *ast);
void	do_echo(t_data *data, t_ast *ast);
void	do_exit(t_data *data, t_ast *ast);
void	do_unset(t_data *data, t_ast *ast);
void	do_export(t_data *data, t_ast *ast);
void	ft_error(t_data *data, char *error);

char	*export_name(t_data *data);
char	*export_value(t_data *data);

t_list	*init_env(char **envp);

#endif

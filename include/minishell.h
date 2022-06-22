/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:10:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/22 17:37:28 by zpalfi           ###   ########.fr       */
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

typedef struct s_cmd
{
	int				infile;
	int				outfile;
	char			*cmd;
	char			**arg;
	char			**tokens;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int		dc;
	int		fd[2];
	int		sc;
	int		dc_2;
	int		sc_2;
	int		erno;
	char	**tokens;
	char	*line;
	int		count;
	int		word;
	int		len;
	int		i;
	int		pipes;
	char	*cmd;
	int		nr;
	int		np;
	char	*home;
	char	*dir;
	char	**first_envp;
	char	**envp;
	t_cmd	*cmd_lst;
}	t_data;

int		sig_handler(void);
int		is_valid_name(char c);
int		this_envp(t_data *data);
int		valid_export(t_data *data);
int		ft_strcmp(char *s, char *d);
int		export_exists(t_data *data);
int		len_env(t_data *data, int i);
int		save_env(t_data *data, int j);
int		token_len(t_data *data, int i);
int		first_envp(t_data *data, char *s);
int		save_env_errno(t_data *data, int j);
int		token_len_errno(t_data *data, int i);
int		token_len_env(t_data *data, int i, int j);
int		save_env_2(t_data *data, int j, char *name);

void	ast(t_data *data);
void	do_cd(t_data *data);
void	parser(t_data *data);
void	do_env(t_data *data);
void	do_pwd(t_data *data);
void	do_echo(t_cmd *cmd);
void	do_exit(t_data *data);
void	do_unset(t_data *data);
void	free_all(t_data *data);
void	print_miniconcha(void);
void	do_export(t_data *data);
void	free_exit(t_data *data);
void	del_one_env(t_data *data);
void	save_tokens(t_data *data);
void	pipe_parser(t_data *data);
void	change_value(t_data *data);
void	count_tokens(t_data *data);
void	do_other(t_data *data, t_cmd *cmd);
void	ft_error(t_data *data, char *error);
void	change(t_data *data, int index, char **new_envp);

char	*export_name(t_data *data, char *env);
char	*export_value(t_data *data, char *env);

t_list	*init_env(t_data *data, char **envp);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:10:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/04 16:34:06 by zpalfi           ###   ########.fr       */
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

typedef struct s_files
{
	int				type;
	char			*filename;
	struct s_files	*next;
}	t_files;

typedef struct s_cmd
{
	int				infile;
	int				outfile;
	int				first_1;
	int				first_2;
	int				aux;
	char			*cmd;
	char			**arg;
	char			**tokens;
	int				*tokens_type;
	t_files			*infiles;
	t_files			*outfiles;
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
	int		*tokens_type;
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
int		do_echo(t_data *data, t_cmd *cmd, int fd);
int		is_valid_name(char c);
int		this_envp(t_data *data, t_cmd *cmd);
int		valid_export(t_data *data, t_cmd *cmd);
int		ft_strcmp(char *s, char *d);
int		export_exists(t_data *data, t_cmd *cmd);
int		do_cd(t_data *data, t_cmd *cmd);
int		len_env(t_data *data, int i);
int		save_env(t_data *data, int j);
int		token_len(t_data *data, int i);
int		malloc_tokens(t_data *data);
int		do_env(t_data *data, t_cmd *cmd, int fd);
int		do_pwd(t_data *data, t_cmd *cmd, int fd);
int		do_exit(t_data *data, t_cmd *cmd);
int		do_export(t_data *data, t_cmd *cmd);
int		do_unset(t_data *data, t_cmd *cmd);
int		first_envp(t_data *data, char *s);
int		save_env_errno(t_data *data, int j);
int		token_len_errno(t_data *data, int i);
int		token_len_env(t_data *data, int i, int j);
int		output_file(t_cmd *n, char **tokens, int z);
int		input_file(t_cmd *n, char **tokens, int z);
int		save_env_2(t_data *data, int j, char *name);

void	ast(t_data *data);
void	parser(t_data *data);
void	free_all(t_data *data);
void	print_miniconcha(void);
void	free_exit(t_data *data);
void	del_one_env(t_data *data);
void	save_tokens(t_data *data);
void	token_len_init(t_data *data);
void	do_path_cmd(t_data *data, t_cmd *cmd);
void	pipe_parser(t_data *data);
void	change_value(t_data *data, t_cmd *cmd);
void	count_tokens(t_data *data);
void	save_tokens_init(t_data *data);
void	do_other(t_data *data, t_cmd *cmd);
void	ft_error(t_data *data, char *error);
void	add_export(t_data *data, t_cmd *cmd);
void	change(t_data *data, t_cmd *cmd, int index, char **new_envp);
void	files_add_back(t_files **files, t_files *new);
void	cmd_add_back(t_cmd	**lst, t_cmd *new);

char	*export_name(t_data *data, char *env);
char	*export_value(t_data *data, char *env);

t_list	*init_env(t_data *data, char **envp);

t_files	*files_lst_new(char *name, int mode, char c);

t_cmd	*cmd_lst_new(t_data *data, char **tokens, int i, int j);

#endif

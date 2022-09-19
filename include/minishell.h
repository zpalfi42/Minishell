/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:10:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 14:08:51 by zpalfi           ###   ########.fr       */
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
	int				end[2];

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
	int				*tokens_type;

	char			*cmd;
	char			**arg;
	char			**tokens;

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
	int		aux;
	int		erno;
	int		count;
	int		word;
	int		len;
	int		i;
	int		z;
	int		pipes;
	int		*tokens_type;
	int		nr;
	int		np;
	int		ast;
	int		j;

	char	*line;
	char	*cmd;
	char	*home;
	char	*dir;

	char	**tokens;
	char	**first_envp;
	char	**envp;
	t_cmd	*cmd_lst;
}	t_data;

int		sig_handler(void);
int		pipe_parser(t_data *data);
int		data_len_up(t_data *data);
int		malloc_tokens(t_data *data);
int		ft_strcmp(char *s, char *d);
int		is_valid_name(char c, int z);
int		len_env(t_data *data, int i);
int		save_env(t_data *data, int j);
int		token_len(t_data *data, int i);
int		find_j(t_data *data, int mode);
int		redir_type(char **tokens, int i);
int		first_envp(t_data *data, char *s);
int		save_env_errno(t_data *data, int j);
int		this_envp(t_data *data, t_cmd *cmd);
int		token_len_errno(t_data *data, int i);
int		is_builtin(t_data *data, t_cmd *cmd);
int		envp_init(t_data *data, char **envp);
int		cmd_add_back(t_cmd	**lst, t_cmd *new);
int		valid_export(t_data *data, t_cmd *cmd);
int		replace_home(t_data *data, t_cmd *cmd);
int		export_exists(t_data *data, t_cmd *cmd);
int		do_cd(t_data *data, t_cmd *cmd, int mode);
int		token_len_env(t_data *data, int i, int j);
int		save_env_2(t_data *data, int j, char *name);
int		do_exit(t_data *data, t_cmd *cmd, int mode);
int		do_unset(t_data *data, t_cmd *cmd, int mode);
int		files_add_back(t_files **files, t_files *new);
int		do_env(t_data *data, t_cmd *cmd, int fd, int mode);
int		do_pwd(t_data *data, t_cmd *cmd, int fd, int mode);
int		do_echo(t_data *data, t_cmd *cmd, int fd, int mode);
int		do_export(t_data *data, t_cmd *cmd, int mode, int fd);
int		input_file(t_cmd *n, char **tokens, int z, t_data *data);
int		output_file(t_cmd *n, char **tokens, int z, t_data *data);

void	ast(t_data *data);
void	handler(int signum);
void	parser(t_data *data);
void	free_all(t_data *data);
void	print_miniconcha(void);
void	free_exit(t_data *data);
void	del_one_env(t_data *data);
void	save_tokens(t_data *data);
void	handler_block(int signum);
void	count_tokens(t_data *data);
void	token_len_init(t_data *data);
void	save_tokens_init(t_data *data);
void	do_other(t_data *data, t_cmd *cmd);
void	ft_error(t_data *data, char *error);
void	exec(t_data *data, int in, int out);
void	save_home_data(t_data *data, int mode);
void	add_export(t_data *data, t_cmd *cmd);
void	do_path_cmd(t_data *data, t_cmd *cmd);
void	change_value(t_data *data, t_cmd *cmd);
void	redirect_io(int in, int out, int mode);
void	do_export_else(t_data *data, t_cmd *cmd);
void	do_dir(t_data *data, t_cmd *cmd, int mode);
void	exec_simple(t_data *data, int in, int out);
void	change_pwd(t_data *data, char *pwd, int mode);
void	assign_io(t_data *data, int *in, int *out, int fd[2]);
void	cmd_tokens_saver(t_cmd *n, t_data *data, int i, int j);
void	exec_builtin(t_data *data, t_cmd *cmd, int fd, int mode);
void	find_cmd_after_redir(char **tokens, t_cmd *n, int i, int j);
void	change(t_data *data, t_cmd *cmd, int index, char **new_envp);
void	change_pwd_value(int index, char **new_envp, char *pwd, int mode);

char	*cd_init(t_data *data);
char	*export_name(t_data *data, char *env);
char	*export_value(t_data *data, char *env);

t_files	*files_heredoc(char *name, int i, t_files *n);
t_files	*files_lst_new(char *name, int mode, char c, int token_type);

t_cmd	*cmd_lst_new(t_data *data, char **tokens, int i, int j);

#endif

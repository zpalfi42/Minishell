/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:10:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/07 17:19:20 by zpalfi           ###   ########.fr       */
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
}	t_data;

int		sig_handler(void);
int		token_len(t_data *data, int i);

void	save_tokens(t_data *data);
void	print_miniconcha(void);
void	count_tokens(t_data *data);
// void	count_words(t_data *data);
// void	save_tokens(t_data *data);

#endif

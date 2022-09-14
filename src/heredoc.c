/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:21:03 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/14 12:23:01 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static char	*get_limiter(char *name, int i)
{
	char			*aux;
	int				j;

	j = 0;
	while (name[j + i] != '\0')
		j++;
	aux = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (name[j + i] != '\0')
	{
		aux[j] = name[j + i];
		j++;
	}
	aux[j] = '\0';
	return (aux);
}

static void	finish_attr(struct termios *attr_out, struct termios *attr_in,
			t_files *n, char *aux)
{
	close(n->end[1]);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, attr_out);
	tcsetattr(STDIN_FILENO, TCSANOW, attr_in);
	free(attr_out);
	free(attr_in);
	free (aux);
	n->filename = NULL;
	n->next = NULL;
}

static void	g_status_get(int fd[2], t_files *n)
{
	g_status = WEXITSTATUS(g_status);
	if (g_status != 130)
		dup2(fd[0], n->end[0]);
	close(fd[0]);
}

t_files	*read_heredoc(char *aux, int fd[2])
{
	char	*buf;

	signal(SIGINT, handler_block);
	while (42)
	{
		buf = readline(">");
		if (!buf)
		{
			break ;
		}
		if (ft_strcmp(buf, aux))
			break ;
		ft_putendl_fd(buf, fd[1]);
		free (buf);
	}
	free (buf);
	close(fd[1]);
	exit(0);
}

t_files	*files_heredoc(char *name, int i, t_files *n)
{
	char			*aux;
	int				fd[2];
	pid_t			pid;
	struct termios	*attr_out;
	struct termios	*attr_in;

	attr_out = (struct termios *)malloc(sizeof(struct termios));
	attr_in = (struct termios *)malloc(sizeof(struct termios));
	if (pipe(n->end) == -1 || pipe(fd) == -1)
	{
		printf("Pipe error\n");
		return (NULL);
	}
	aux = get_limiter(name, i);
	tcgetattr(STDOUT_FILENO, attr_out);
	tcgetattr(STDIN_FILENO, attr_in);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		read_heredoc(aux, fd);
	close(fd[1]);
	waitpid(pid, &g_status, 0);
	g_status_get(fd, n);
	finish_attr(attr_out, attr_in, n, aux);
	return (n);
}

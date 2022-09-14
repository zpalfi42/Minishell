/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:33:12 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/14 11:46:23 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

t_files	*files_heredoc_2(char *aux, t_files *n, int fd[2])
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
	free (aux);
	n->filename = NULL;
	n->next = NULL;
	exit(0);
}

char	*get_limiter(char *name, int i)
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

t_files	*files_heredoc(char *name, int i, t_files *n)
{
	char			*aux;
	int				fd[2];
	pid_t			pid;
	struct termios	*attr_out;
	struct termios	*attr_in;
	int				status;

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
		files_heredoc_2(aux, n, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, attr_out);
	tcsetattr(STDIN_FILENO, TCSANOW, attr_in);
	free(attr_out);
	free(attr_in);
	close(n->end[1]);
	if (status == 33280)
		g_status = 130;
	if (g_status != 130)
		dup2(fd[0], n->end[0]);
	printf("%d\n", g_status);
	close(fd[0]);
	return (n);
}

t_files	*files_normal(char *name, int i, t_files *n)
{
	int	j;

	j = 0;
	while (name[j + i] != '\0')
		j++;
	n->filename = malloc(sizeof(char) * (j + 1));
	j = -1;
	while (name[++j + i] != '\0')
		n->filename[j] = name[j + i];
	n->next = NULL;
	return (n);
}

char	*is_redir(char *name)
{
	if ((ft_strnstr(name, ">", ft_strlen(name)) != NULL
			|| ft_strnstr(name, ">>", ft_strlen(name)) != NULL
			|| ft_strnstr(name, "<", ft_strlen(name)) != NULL
			|| ft_strnstr(name, "<<", ft_strlen(name)) != NULL))
	{
		return (NULL);
	}
	return (name);
}

t_files	*files_lst_new(char *name, int mode, char c, int token_type)
{
	t_files	*n;
	int		i;
	int		j;

	if (is_redir(name) == NULL && token_type == 0)
	{
		printf("Syntax error near unexpected token '%s'\n", name);
		return (NULL);
	}
	i = 0;
	j = 2;
	if (mode == 2)
		j = 1;
	n = (t_files *)malloc(sizeof(t_files));
	if (!n)
		return (NULL);
	n->type = mode;
	while (name[i] == c && i < j)
		i++;
	if (mode == 3)
		return (files_heredoc(name, i, n));
	return (files_normal(name, i, n));
}

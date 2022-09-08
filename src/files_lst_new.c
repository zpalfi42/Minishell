/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:33:12 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/08 13:28:31 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*files_heredoc_2(char *aux, t_files *n)
{
	char	*buf;

	while (42)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		if (ft_strcmp(buf, aux))
			break ;
		ft_putendl_fd(buf, n->end[1]);
		free (buf);
	}
	free (buf);
	close(n->end[1]);
	free (aux);
	n->filename = NULL;
	n->next = NULL;
	return (n);
}

t_files	*files_heredoc(char *name, int i, t_files *n)
{
	char	*aux;
	int		j;

	if (pipe(n->end) == -1)
	{
		printf("Pipe error\n");
		return (NULL);
	}
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
	return (files_heredoc_2(aux, n));
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

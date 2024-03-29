/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:33:12 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:52:45 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* files_normal() saves the filename info inside the t_files struct if
* the file is not a heredoc.
*/

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
	n->filename[j] = '\0';
	n->next = NULL;
	return (n);
}

/*
* is_redir() checks if name is only a redirection and returns NULL,
* else returns name.
*/

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

/*
*files_lst_new() creates and returns a t_files struct with all the information
* of the file that is beeing saved. If a heredoc is needed it calls
* files_heredoc(), else it calls files_normal.
*/

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:38:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/28 15:58:38 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*last_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd	**lst, t_cmd *new)
{
	t_cmd	*t;

	if (!lst || !new)
		return ;
	t = *lst;
	if (*lst)
	{
		t = last_cmd(*lst);
		t->next = new;
	}
	else
		*lst = new;
}

t_files	*last_files(t_files	*files)
{
	if (!files)
		return (NULL);
	while (files->next)
		files = files->next;
	return (files);
}

void	files_add_back(t_files **files, t_files *new)
{
	t_files	*t;

	if (!files || !new)
		return ;
	t = *files;
	if (*files)
	{
		t = last_files(*files);
		t->next = new;
	}
	else
		*files = new;
}

t_files	*files_lst_new(char *name, int mode, char c)
{
	t_files	*n;
	int		i;
	int		j;

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

t_cmd	*cmd_lst_new(char **tokens, int i, int j)
{
	t_cmd	*n;
	int		z;
	int		first;

	n = (t_cmd *)malloc(sizeof(t_cmd));
	if (!n)
		return (NULL);
	n->cmd = tokens[i];
	n->arg = malloc(sizeof(char *) * (j - i));
	z = i;
	while (tokens[z] != 0 && z < j)
	{
		if (tokens[z][0] == '<' || tokens[z][0] == '>')
			break ;
		z++;
	}
	n->tokens = malloc(sizeof(char *) * (z - i + 1));
	first = 1;
	z = i;
	while (tokens[z] != 0 && z < j)
	{
		if (tokens[z][0] == '>')
		{
			if (tokens[z][1] == '\0')
			{
				if (first == 1)
				{
					n->files = files_lst_new(tokens[++z], 0, '>');
					first = 0;
				}
				else
					files_add_back(&n->files, files_lst_new(tokens[++z], 0, '>'));
			}
			else if (tokens[z][1] == '>')
			{
				if (tokens[z][2] == '\0')
				{
					if (first == 1)
					{
						n->files = files_lst_new(tokens[++z], 1, '>');
						first = 0;
					}
					else
						files_add_back(&n->files, files_lst_new(tokens[++z], 1, '>'));
				}
				else
				{
					if (first == 1)
					{
						n->files = files_lst_new(tokens[z], 1, '>');
						first = 0;
					}
					else
						files_add_back(&n->files, files_lst_new(tokens[z], 1, '>'));
				}
			}
			else
			{
				if (first == 1)
				{
					n->files = files_lst_new(tokens[z], 0, '>');
					first = 0;
				}
				else
					files_add_back(&n->files, files_lst_new(tokens[z], 0, '>'));
			}
		}
		else if (tokens[z][0] == '<')
		{
			if (tokens[z][1] == '\0')
			{
				if (first == 1)
				{
					n->files = files_lst_new(tokens[++z], 2, '<');
					first = 0;
				}
				else
					files_add_back(&n->files, files_lst_new(tokens[++z], 2, '<'));
			}
			else
			{
				if (first == 1)
				{
					n->files = files_lst_new(tokens[z], 2, '<');
					first = 0;
				}
				else
					files_add_back(&n->files, files_lst_new(tokens[z], 2, '<'));
			}
		}
		z++;
	}
	if (first == 1)
		n->files = NULL;
	z = 0;
	n->tokens[z] = tokens[i];
	while (tokens[++i] != 0 && tokens[i][0] != '<' && tokens[i][0] != '>')
	{
		n->arg[z] = tokens[i];
		n->tokens[z + 1] = tokens[i];
		z++;
	}
	n->arg[z] = 0;
	n->tokens[z + 1] = 0;
	n->next = NULL;
	return (n);
}

void	pipe_parser(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->pipes = 0;
	while (data->tokens[++i] != 0)
	{
		if (ft_strcmp(data->tokens[i], "|\0"))
			data->pipes++;
	}
	i = -1;
	while (data->tokens[++i] != 0)
		if (ft_strcmp(data->tokens[i], "|\0"))
			break ;
	data->cmd_lst = cmd_lst_new(data->tokens, 0, i);
	while (data->pipes > 0)
	{
		j = i + 1;
		while (data->tokens[++i] != 0)
			if (ft_strcmp(data->tokens[i], "|\0"))
				break ;
		cmd_add_back(&data->cmd_lst, cmd_lst_new(data->tokens, j, i));
		data->pipes--;
	}
}

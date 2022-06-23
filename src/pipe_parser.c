/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:38:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/23 14:49:23 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// printf("--> cmd = %s || arg[0] = %s\n",
// data->cmd_lst->cmd, data->cmd_lst->arg[0]);
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

t_cmd	*cmd_lst_new(char **tokens, int i, int j)
{
	t_cmd	*n;
	int		z;

	n = (t_cmd *)malloc(sizeof(t_cmd));
	if (!n)
		return (NULL);
	n->cmd = tokens[i];
	n->arg = malloc(sizeof(char *) * (j - i));
	n->tokens = malloc(sizeof(char *) * (j - i + 1));
	z = 0;
	n->tokens[z] = tokens[i];
	while (tokens[++i] != 0 && i < j)
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

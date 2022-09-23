/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:49:44 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/23 12:06:30 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*n;

	while (cmd && *cmd)
	{
		n = (*cmd)->next;
		free((*cmd)->arg);
		free((*cmd)->tokens);
		free((*cmd)->tokens_type);
		free((*cmd));
		*cmd = n;
	}
}

void	free_all(t_data *data, int mode)
{
	int		i;

	i = 0;
	if (data->line != 0)
	{
		if (mode == 0)
			free_cmd(&data->cmd_lst);
		while (data->tokens[i] != 0)
		{
			free(data->tokens[i]);
			i++;
		}
		free(data->tokens_type);
		free(data->tokens);
	}
}

void	free_exit(t_data *data)
{
	int	i;

	free_all(data, 0);
	i = 0;
	while (data->envp[i] != 0)
	{
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
	i = 0;
	while (data->first_envp[i] != 0)
	{
		free(data->first_envp[i]);
		i++;
	}
	free(data->first_envp);
	free(data->home);
	free(data);
}

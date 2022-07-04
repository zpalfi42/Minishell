/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:02:48 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/04 14:41:56 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_comand(char **mypaths, char *cmd)
{
	char	*tmp;
	char	*comand;

	while (*mypaths)
	{
		tmp = ft_strjoin(*mypaths, "/");
		comand = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(comand, 0) == 0)
			return (comand);
		free(comand);
		mypaths++;
	}
	return (NULL);
}

static void	exec_other(t_data *data, t_cmd *cmd)
{
	char	**paths;
	char	*comand;
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (data->envp[i] != 0)
	{
		if (!ft_strncmp(data->envp[i], "PATH=", 5))
		{
			value = export_value(data, data->envp[i]);
			break ;
		}
		i++;
	}
	paths = ft_split(value, ':');
	comand = get_comand(paths, cmd->cmd);
	if (!comand)
	{
		free(comand);
		free(paths);
		printf("\033[1;31mCommand not found :(\n");
	}
	execve(comand, cmd->tokens, data->envp);
}

void	do_other(t_data *data, t_cmd *cmd)
{
	exec_other(data, cmd);
}

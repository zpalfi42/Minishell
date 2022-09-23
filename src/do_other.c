/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:02:48 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/23 12:21:47 by zpalfi           ###   ########.fr       */
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

void	command_not_found(char *comand, char **paths, char *value)
{
	int	i;

	if (!comand)
	{
		free(comand);
		i = 0;
		while (paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths);
		free(value);
		ft_putstr_fd("command not found\n", 1);
		exit (127);
	}
}

void	free_aux_params(char **paths, char *value)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	free(value);
}

static void	exec_other(t_data *data, t_cmd *cmd)
{
	char	**paths;
	char	*comand;
	char	*value;
	int		i;

	i = -1;
	value = NULL;
	while (data->envp[++i] != 0)
	{
		if (!ft_strncmp(data->envp[i], "PATH=", 5))
		{
			value = export_value(data, data->envp[i]);
			break ;
		}
	}
	paths = ft_split(value, ':');
	comand = get_comand(paths, cmd->cmd);
	command_not_found(comand, paths, value);
	free_aux_params(paths, value);
	if (execve(comand, cmd->tokens, data->envp) == -1)
		exit (126);
	exit (0);
}

void	do_other(t_data *data, t_cmd *cmd)
{
	exec_other(data, cmd);
}

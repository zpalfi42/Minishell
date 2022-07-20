/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/20 16:49:14 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_exists(t_data *data, t_cmd *cmd)
{
	char	*name;
	char	*envp_name;
	int		i;

	name = export_name(data, cmd->tokens[data->i]);
	i = -1;
	while (data->envp[++i] != 0)
	{
		envp_name = export_name(data, data->envp[i]);
		if (ft_strcmp(envp_name, name))
		{
			i = -1;
			break ;
		}
		free(envp_name);
	}
	free(name);
	return (i);
}

int	valid_export(t_data *data, t_cmd *cmd)
{
	int	i;
	int	aux;

	(void) data;
	aux = 1;
	i = 0;
	if (((65 > cmd->tokens[data->i][0] || cmd->tokens[data->i][0] > 90)
		&& (97 > cmd->tokens[data->i][0] || cmd->tokens[data->i][0] > 122))
		&& cmd->tokens[data->i][0] != 95)
		return (1);
	while (cmd->tokens[data->i][++i])
	{
		if (cmd->tokens[data->i][i] == '=' && aux != 0)
			aux = 0;
		else if (is_valid_name(cmd->tokens[data->i][i], i) == 0 && aux != 0)
			return (1);
	}
	return (aux);
}

int	do_export(t_data *data, t_cmd *cmd, int mode)
{
	int	i;

	data->i = 1;
	while (cmd->tokens[data->i] != 0)
	{
		if (valid_export(data, cmd))
		{
			printf("\033[1;31mInvalid export %s!\n", cmd->tokens[data->i]);
			data->erno = 1;
		}
		else
		{
			i = export_exists(data, cmd);
			if (i == -1)
				change_value(data, cmd);
			else if (i != -2)
				add_export(data, cmd);
		}
		data->i++;
	}
	if (mode == 1)
		exit (1);
	return (1);
}

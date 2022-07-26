/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/26 16:28:12 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_data *data, int fd)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(data->envp[i], fd);
		i++;
	}
}

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
		printf("%s --> %s =? %s\n", data->envp[i], name, envp_name);
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

int	do_export(t_data *data, t_cmd *cmd, int mode, int fd)
{
	int	i;

	data->i = 1;
	if (cmd->tokens[data->i] == NULL)
		print_export(data, fd);
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
			// printf("--> %d\n", i);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:35:19 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 12:27:52 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	valid_name(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
		if (!is_valid_name(name[i], i))
			return (1);
	return (0);
}

int	in_envp(t_data *data, t_cmd *cmd)
{
	char	*name;
	char	*envp_name;
	int		i;
	int		j;

	name = export_name(data, cmd->tokens[1]);
	i = -1;
	j = 0;
	while (data->envp[++i] != 0 && j == 0)
	{
		envp_name = export_name(data, data->envp[i]);
		if (ft_strcmp(envp_name, name))
			j = -1;
		free(envp_name);
	}
	free(name);
	if (j == -1)
		return (i - 1);
	return (-1);
}

static char	**assign_new(t_data *data, char **new_envp, int j)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (data->envp[i] != 0)
	{
		if (i == j)
		{
			free(data->envp[i]);
			i++;
		}
		else
		{
			new_envp[z] = malloc(sizeof(char) * ft_strlen(data->envp[i]));
			ft_strlcpy(new_envp[z], data->envp[i],
				ft_strlen(data->envp[i]) + 1);
			free(data->envp[i]);
			i++;
			z++;
		}
	}
	free(data->envp);
	new_envp[z] = 0;
	return (new_envp);
}

void	print_unset_error(t_cmd *cmd)
{
	ft_putstr_fd("unset: ", 1);
	ft_putstr_fd(cmd->tokens[1], 1);
	ft_putstr_fd(": not a valid identifier\n", 1);
}

int	do_unset(t_data *data, t_cmd *cmd, int mode)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = in_envp(data, cmd);
	if (valid_name(cmd->tokens[1]))
	{
		print_unset_error(cmd);
		g_status = 1;
		if (mode == 1)
			exit (1);
	}
	else if (j != -1)
	{
		while (data->envp[i] != 0)
			i++;
		new_envp = malloc(sizeof(char *) * (i));
		new_envp = assign_new(data, new_envp, j);
		data->envp = new_envp;
		g_status = 0;
	}
	if (mode == 1)
		exit (0);
	return (1);
}

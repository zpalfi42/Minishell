/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:35:19 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/20 16:50:44 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			i++;
		else
		{
			new_envp[z] = malloc(sizeof(char) * ft_strlen(data->envp[i]));
			ft_strlcpy(new_envp[z], data->envp[i],
				ft_strlen(data->envp[i]) + 1);
			i++;
			z++;
		}
	}
	new_envp[z] = 0;
	return (new_envp);
}

int	do_unset(t_data *data, t_cmd *cmd, int mode)
{
	char	**new_envp;
	int		i;
	int		j;
	int		z;

	z = 0;
	i = 0;
	j = in_envp(data, cmd);
	if (valid_name(cmd->tokens[1]))
		printf("\033[1;31m%s is not a valid name!\n", cmd->tokens[1]);
	else if (j != -1)
	{
		while (data->envp[i] != 0)
			i++;
		new_envp = malloc(sizeof(char *) * (i));
		new_envp = assign_new(data, new_envp, j);
		free(data->envp);
		data->envp = new_envp;
	}
	else
		printf("\033[1;31mCannot unset %s\n", cmd->tokens[1]);
	if (mode == 1)
		exit (1);
	return (1);
}

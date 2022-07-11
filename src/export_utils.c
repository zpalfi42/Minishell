/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:50 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/11 15:55:21 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_name(t_data *data, char *env)
{
	char	*ret;
	int		i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	ret = malloc(sizeof(char) * i);
	if (!ret)
		ft_error(data, "Failed malloc :(");
	i = -1;
	while (env[++i] != '=' && env[i] != '\0')
		ret[i] = env[i];
	ret[i] = '\0';
	return (ret);
}

char	*export_value(t_data *data, char *env)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i++] != '=')
	j = 0;
	while (env[i + j] != '\0')
		j++;
	ret = malloc(sizeof(char) * j);
	if (!ret)
		ft_error(data, "Failed malloc :(");
	j = -1;
	while (env[i + ++j] != '\0')
		ret[j] = env[i + j];
	ret[j] = '\0';
	return (ret);
}

int	this_envp(t_data *data, t_cmd *cmd)
{
	char	*name;
	char	*env_name;
	int		i;
	int		j;

	name = export_name(data, cmd->tokens[1]);
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		env_name = export_name(data, data->envp[i]);
		if (ft_strcmp(name, env_name))
		{
			j = -1;
			break ;
		}
		free(env_name);
		i++;
	}
	if (j == -1)
		free(env_name);
	free(name);
	return (i);
}

void	change(t_data *data, t_cmd *cmd, int index, char **new_envp)
{
	char	*new_value;
	char	*new_name;
	int		i;
	int		j;

	new_value = export_value(data, cmd->tokens[1]);
	new_name = export_name(data, data->envp[index]);
	new_envp[index] = malloc(sizeof(char)
			* (ft_strlen(new_name) + ft_strlen(new_value)));
	i = 0;
	j = -1;
	while (new_name[i])
	{
		new_envp[index][i] = new_name[i];
		i++;
	}
	new_envp[index][i] = '=';
	i++;
	while (new_value[++j])
	{
		new_envp[index][i] = new_value[j];
		i++;
	}
	new_envp[index][i] = '\0';
}

void	change_value(t_data *data, t_cmd *cmd)
{
	char	**new_envp;
	int		i;
	int		j;

	j = this_envp(data, cmd);
	i = 0;
	while (data->envp[i] != 0)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (data->envp[i] != 0)
	{
		if (j == i)
			change(data, cmd, i, new_envp);
		else
		{
			new_envp[i] = malloc(sizeof(char) * (ft_strlen(data->envp[i]) + 1));
			ft_strlcpy(new_envp[i], data->envp[i],
				ft_strlen(data->envp[i]) + 1);
		}
		i++;
	}
	free(data->envp);
	new_envp[i] = 0;
	data->envp = new_envp;
}

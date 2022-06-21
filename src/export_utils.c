/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:50 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/21 14:57:24 by zpalfi           ###   ########.fr       */
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

int	valid_export(t_data *data)
{
	int	i;
	int	aux;

	aux = 1;
	i = 0;
	if (((65 > data->tokens[1][0] || data->tokens[1][0] > 90)
		&& (97 > data->tokens[1][0] || data->tokens[1][0] > 122))
		&& data->tokens[1][0] != 95)
		return (1);
	while (data->tokens[1][++i])
	{
		if (data->tokens[1][i] == '=' && aux != 0)
			aux = 0;
		else if (is_valid_name(data->tokens[1][i]) == 0 && aux != 0)
			return (1);
	}
	return (aux);
}

int	this_envp(t_data *data)
{
	char	*name;
	char	*env_name;
	int		i;
	int		j;

	name = export_name(data, data->tokens[1]);
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

void	change(t_data *data, int index, char **new_envp)
{
	char	*new_value;
	char	*new_name;
	int		i;
	int		j;

	new_value = export_value(data, data->tokens[1]);
	new_name = export_name(data, data->envp[index]);
	new_envp[index] = malloc(sizeof(char)
			* (ft_strlen(new_name) + ft_strlen(new_value)));
	i = 0;
	j = 0;
	while (new_name[i])
	{
		new_envp[index][i] = new_name[i];
		i++;
	}
	new_envp[index][i] = '=';
	i++;
	while (new_value[j])
	{
		new_envp[index][i] = new_value[j];
		i++;
		j++;
	}
	new_envp[index][i] = '\0';
}

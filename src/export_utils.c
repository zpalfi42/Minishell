/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:50 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 15:58:42 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Takes a velue after '=' of line introduced after command.

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
	ret = malloc(sizeof(char) * j + 1);
	if (!ret)
		ft_error(data, "Failed malloc :(");
	j = -1;
	while (env[i + ++j] != '\0')
		ret[j] = env[i + j];
	ret[j] = '\0';
	return (ret);
}

//this function, search the enviorment variable that we will replace.

int	pos_in_envp(t_data *data, t_cmd *cmd)
{
	char	*name;
	char	*env_name;
	int		i;
	int		j;

	name = export_name(data, cmd->tokens[data->i]);
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		env_name = export_name(data, data->envp[i]);
		if (ft_strcmp(name, env_name))
		{
			j = -1;
			free(env_name);
			break ;
		}
		free(env_name);
		i++;
	}
	free(name);
	return (i);
}

//Second part to change_value function.

void	change(t_data *data, t_cmd *cmd, int index, char **new_envp)
{
	char	*new_value;
	char	*new_name;
	int		i;
	int		j;

	new_value = export_value(data, cmd->tokens[data->i]);
	new_name = export_name(data, data->envp[index]);
	new_envp[index] = malloc(sizeof(char)
			* (ft_strlen(new_name) + ft_strlen(new_value) + 2));
	i = -1;
	j = -1;
	while (new_name[++i])
		new_envp[index][i] = new_name[i];
	new_envp[index][i] = '=';
	i++;
	while (new_value[++j])
	{
		new_envp[index][i] = new_value[j];
		i++;
	}
	new_envp[index][i] = '\0';
	free(new_name);
	free(new_value);
}

//This function do a new nvp and change the value of 
//enviorment variable when already exist.

void	change_value(t_data *data, t_cmd *cmd)
{
	char	**new_envp;
	int		i;
	int		j;

	j = pos_in_envp(data, cmd);
	i = 0;
	while (data->envp[i] != 0)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (data->envp[++i] != 0)
	{
		if (j == i)
			change(data, cmd, i, new_envp);
		else
		{
			new_envp[i] = malloc(sizeof(char) * (ft_strlen(data->envp[i]) + 1));
			ft_strlcpy(new_envp[i], data->envp[i],
				ft_strlen(data->envp[i]) + 1);
		}
		free(data->envp[i]);
	}
	free(data->envp);
	new_envp[i] = 0;
	data->envp = new_envp;
}

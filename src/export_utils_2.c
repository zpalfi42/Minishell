/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:56:34 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/21 14:58:55 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_value(t_data *data)
{
	char	**new_envp;
	int		i;
	int		j;

	j = this_envp(data);
	i = 0;
	while (data->envp[i] != 0)
		i++;
	new_envp = malloc(sizeof(char *) * i);
	i = 0;
	while (data->envp[i] != 0)
	{
		if (j == i)
			change(data, i, new_envp);
		else
		{
			new_envp[i] = malloc(sizeof(char) * ft_strlen(data->envp[i]));
			ft_strlcpy(new_envp[i], data->envp[i],
				ft_strlen(data->envp[i]) + 1);
		}
		i++;
	}
	free(data->envp);
	new_envp[i] = 0;
	data->envp = new_envp;
}

int	first_envp(t_data *data, char *s)
{
	int		i;
	char	*name;

	i = 0;
	while (data->first_envp[i])
	{
		name = export_name(data, data->first_envp[i]);
		if (ft_strcmp(name, s))
			return (1);
		free(name);
		i++;
	}
	return (0);
}

int	export_exists(t_data *data)
{
	char	*name;
	char	*envp_name;
	int		i;

	name = export_name(data, data->tokens[1]);
	i = -1;
	while (data->envp[++i] != 0)
	{
		envp_name = export_name(data, data->envp[i]);
		if (ft_strcmp(envp_name, name))
		{
			if (first_envp(data, name))
				i = -2;
			else
				i = -1;
			break ;
		}
		free(envp_name);
	}
	if (i == -2)
		printf("\033[1;31mCan't change %s value!\n", name);
	free(name);
	return (i);
}

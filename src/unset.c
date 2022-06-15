/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:35:19 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/15 17:14:08 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_envp(t_data *data)
{
	char	*name;
	char	*envp_name;
	int		i;
	int		j;

	name = export_name(data, data->tokens[1]);
	i = 0;
	j = 0;
	while (data->envp[i] != 0)
	{
		envp_name = export_name(data, data->envp[i]);
		if (ft_strcmp(envp_name, name))
		{
			j = -1;
			break ;
		}
		free(envp_name);
		i++;
	}
	if (j == -1)
	{
		free(envp_name);
		free(name);
		return (i);
	}
	free(name);
	return (-1);
}

void	do_unset(t_data *data)
{
	char	**new_envp;
	char	*name;
	int		i;
	int		j;
	int		z;

	z = 0;
	i = 0;
	j = in_envp(data);
	name = export_name(data, data->tokens[1]);
	if (j != -1 && !first_envp(data, name))
	{
		while (data->envp[i] != 0)
			i++;
		new_envp = malloc(sizeof(char *) * (i - 1));
		i = 0;
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
		free(data->envp);
		data->envp = new_envp;
	}
}

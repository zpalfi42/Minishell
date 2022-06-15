/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/15 17:14:12 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_export(t_data *data)
{
	int		i;
	int		j;
	int		z;
	char	**new_envp;
	char	*name;
	char	*value;

	i = 0;
	j = 0;
	z = 0;
	while (data->envp[i] != 0)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		ft_error(data, "Failed malloc :(");
	name = export_name(data, data->tokens[1]);
	value = export_value(data, data->tokens[1]);
	i = 0;
	while (data->envp[i] != 0)
	{
		new_envp[i] = malloc(sizeof(char) * (ft_strlen(data->envp[i])));
		ft_strlcpy(new_envp[i], data->envp[i], (ft_strlen(data->envp[i]) + 1));
		i++;
	}
	new_envp[i] = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value)));
	while (name[j] != '\0')
	{
		new_envp[i][j] = name[j];
		j++;
	}
	new_envp[i][j] = '=';
	j++;
	while (value[z] != '\0')
	{
		new_envp[i][j] = value[z];
		z++;
		j++;
	}
	new_envp[i][j] = '\0';
	new_envp[i + 1] = 0;
	free(data->envp);
	data->envp = new_envp;
}

void	do_export(t_data *data)
{
	int	i;

	if (valid_export(data))
		printf("\033[1;31mInvalid export!\n");
	else
	{
		i = export_exists(data);
		if (i == -1)
			change_value(data);
		else if (i != -2)
			add_export(data);
	}
}

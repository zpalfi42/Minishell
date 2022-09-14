/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:39:27 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/14 13:16:34 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	is_valid_name(char c, int z)
{
	if ((47 < c && c < 58) || (64 < c && c < 91)
		|| (96 < c && c < 123) || (c == 95))
	{
		if (z == 0 && (47 < c && c < 58))
			return (2);
		return (1);
	}
	return (0);
}

int	save_env_errno(t_data *data, int j)
{
	char	*serrno;
	int		i;

	data->i += 2;
	serrno = ft_itoa(g_status);
	i = 0;
	while (serrno[i] != '\0')
	{
		data->tokens[data->word][j] = serrno[i];
		i++;
		j++;
	}
	return (j);
}

int	save_env_2(t_data *data, int j, char *name)
{
	int		z;
	int		i;
	char	*envp_name;
	char	*envp_value;

	z = 0;
	i = 0;
	while (data->envp[i])
	{
		envp_name = export_name(data, data->envp[i]);
		if (ft_strcmp(envp_name, name))
		{
			envp_value = export_value(data, data->envp[i]);
			while (envp_value[z])
			{
				data->tokens[data->word][j] = envp_value[z];
				z++;
				j++;
			}
		}
		i++;
	}
	return (j);
}

void	save_env_name(t_data *data, char *name)
{
	int	z;

	z = 0;
	while (is_valid_name(data->line[data->i], z))
	{
		if (is_valid_name(data->line[data->i], z) == 2)
		{
			name[z] = data->line[data->i];
			z++;
			data->i++;
			break ;
		}
		name[z] = data->line[data->i];
		z++;
		data->i++;
	}
	name[z] = '\0';
}

int	save_env(t_data *data, int j)
{
	int		z;
	char	*name;

	data->i++;
	z = 0;
	while (is_valid_name(data->line[data->i + z], z))
	{
		if (is_valid_name(data->line[data->i + z], z) == 2)
		{
			z += 2;
			break ;
		}
		z++;
	}
	name = malloc(sizeof(char) * z);
	if (!name)
		ft_error(data, "Failed malloc :(");
	save_env_name(data, name);
	j = save_env_2(data, j, name);
	free(name);
	return (j);
}

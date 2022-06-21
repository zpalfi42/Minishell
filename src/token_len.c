/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:30:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/21 16:03:29 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_len_dc(t_data *data, int i)
{
	i++;
	data->dc--;
	while (data->line[i] != 34 && data->line[i] != '\0')
	{
		if (data->line[i] == '$')
			i = token_len_env(data, i, 0);
		else
		{
			i++;
			data->len++;
		}
	}
	if (data->line[i] == 34)
	{
		data->dc--;
		i++;
	}
	return (i);
}

static int	token_len_sc(t_data *data, int i)
{
	i++;
	data->sc--;
	while (data->line[i] != 39 && data->line[i] != '\0')
	{
		i++;
		data->len++;
	}
	if (data->line[i] == 39)
	{
		data->sc--;
		i++;
	}
	return (i);
}

int	token_len_env(t_data *data, int i, int j)
{
	char	*name;
	char	*envp_name;
	int		z;

	i++;
	while (is_valid_name(data->line[i + j]))
		j++;
	name = malloc(sizeof(char) * j);
	if (!name)
		ft_error(data, "Failed malloc :(");
	j = -1;
	while (++j && is_valid_name(data->line[i + j]))
		name[j] = data->line[i + j];
	name[j] = '\0';
	z = -1;
	while (data->envp[++z] != 0)
	{
		envp_name = export_name(data, data->envp[z]);
		if (ft_strcmp(envp_name, name))
			data->len += ft_strlen(envp_name);
		free(envp_name);
	}
	free(name);
	return (i + j);
}

int	token_len_errno(t_data *data, int i)
{
	char	*serrno;

	serrno = ft_itoa(data->erno);
	data->len += ft_strlen(serrno);
	return (i + 2);
}

int	token_len(t_data *data, int i)
{
	data->len = 0;
	data->dc = data->dc_2;
	data->sc = data->sc_2;
	while (data->line[i] != '\0')
	{
		while (data->line[i] != ' ' && data->line[i] != '\0')
		{
			if (data->line[i] == '$')
				i = len_env(data, i);
			if (data->line[i] == 34 && data->dc > 1)
				i = token_len_dc(data, i);
			else if (data->line[i] == 39 && data->sc > 1)
				i = token_len_sc(data, i);
			else
			{
				data->len++;
				i++;
			}
		}
		if (data->line[i] == ' ' || data->line[i] == '\0')
			break ;
	}
	data->len++;
	return (i + 1);
}

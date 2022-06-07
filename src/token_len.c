/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:30:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/07 17:03:42 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_len_dc(t_data *data, int i)
{
	i++;
	data->dc--;
	while (data->line[i] != 34 && data->line[i] != '\0')
	{
		i++;
		data->len++;
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

int	token_len(t_data *data, int i)
{
	data->len = 0;
	data->dc = data->dc_2;
	data->sc = data->sc_2;
	while (data->line[i] != '\0')
	{
		while (data->line[i] != ' ' && data->line[i] != '\0')
		{
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
		{
			i++;
			break ;
		}
	}
	data->len++;
	return (i);
}

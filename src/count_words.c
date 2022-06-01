/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:04:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/01 15:31:51 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dc_case(t_data *data, int i)
{
	data->n_dc--;
	i++;
	if (data->line[i] == '"')
		i++;
	else if (data->n_dc != 0)
	{
		data->count++;
		while (data->line[i] && data->line[i] != '"')
		{
			if (data->line[i] == 39)
				data->n_sc--;
			i++;
		}
		i++;
	}
	return (i);
}

static int	sc_case(t_data *data, int i)
{
	data->n_sc--;
	i++;
	if (data->line[i] == 39)
		i++;
	else if (data->n_sc != 0)
	{
		data->count++;
		while (data->line[i] && data->line[i] != 39)
		{
			if (data->line[i] == '"')
				data->n_dc--;
			i++;
		}
		i++;
	}
	return (i);
}

void	count_words(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == ' ')
			i++;
		else if (data->line[i] == '"')
		{
			i = dc_case(data, i);
		}
		else if (data->line[i] == 39)
		{
			i = sc_case(data, i);
		}
		else
		{
			data->count++;
			while (data->line[i] && data->line[i] != ' ')
				i++;
		}
	}
}
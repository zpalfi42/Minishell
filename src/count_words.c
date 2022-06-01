/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:04:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/01 15:56:43 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dc_case(t_data *data, int i)
{
	data->dc--;
	i++;
	if (data->line[i] == '"')
		i++;
	else if (data->dc != 0)
	{
		data->count++;
		while (data->line[i] && data->line[i] != '"')
		{
			if (data->line[i] == 39)
				data->sc--;
			i++;
		}
		i++;
	}
	return (i);
}

static int	sc_case(t_data *data, int i)
{
	data->sc--;
	i++;
	if (data->line[i] == 39)
		i++;
	else if (data->sc != 0)
	{
		data->count++;
		while (data->line[i] && data->line[i] != 39)
		{
			if (data->line[i] == '"')
				data->dc--;
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
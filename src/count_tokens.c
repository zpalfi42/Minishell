/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:32:18 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/07 16:39:52 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens_dc(t_data *data, int i)
{
	i++;
	data->dc--;
	while (data->line[i] != 34 && data->line[i] != '\0')
		i++;
	if (data->line[i] == 34)
	{
		data->dc--;
		i++;
	}
	return (i);
}

static int	count_tokens_sc(t_data *data, int i)
{
	i++;
	data->sc--;
	while (data->line[i] != 39 && data->line[i] != '\0')
		i++;
	if (data->line[i] == 39)
	{
		data->sc--;
		i++;
	}
	return (i);
}

void	count_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i] != '\0')
	{
		while (data->line[i] != ' ' && data->line[i] != '\0')
		{
			if (data->line[i] == 34 && data->dc > 1)
				i = count_tokens_dc(data, i);
			else if (data->line[i] == 39 && data->sc > 1)
				i = count_tokens_sc(data, i);
			else
				i++;
		}
		if (data->line[i] == ' ')
			i++;
		data->count++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:32:18 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:50:00 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* count_tokens_dc() parses data->line until it finds another dquote.
*/

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

/*
* count_tokens_sc() parses data->line until it finds another squote.
*/

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

/*
* count_tokens() parses data->line and count all the tokens that are in it.
* When it finds a dquote it calls count_tokens_dc(), and if it finds a squote
* count_tokens_sc() is called.
*/

void	count_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i] != '\0')
	{
		while (data->line[i] == ' ' && data->line[i] != '\0')
			i++;
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

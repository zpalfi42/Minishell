/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:51:08 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/20 16:49:20 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	countq(t_data *data)
{
	int	i;

	i = 0;
	data->dc = 0;
	data->sc = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == 34)
			data->dc++;
		else if (data->line[i] == 39)
			data->sc++;
		i++;
	}
	data->dc_2 = data->dc;
	data->sc_2 = data->sc;
}

void	parser(t_data *data)
{
	data->i = 0;
	countq(data);
	count_tokens(data);
	save_tokens(data);
}

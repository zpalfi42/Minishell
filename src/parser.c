/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:51:08 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:55:18 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* count_quotes() parses data->line to find dquotes or squotes. When one of them
* are found it increases either data->dc (dquotes) or data->sc (squotes).
*/

static void	count_quotes(t_data *data)
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

/*
* parser() first counts de dquotes and squotes that are found in data->line.
* Then with the info of the numer of quotes, counts the tokens to finally save
* them in a char** called data->tokens.
*/

void	parser(t_data *data)
{
	data->i = 0;
	count_quotes(data);
	count_tokens(data);
	save_tokens(data);
}

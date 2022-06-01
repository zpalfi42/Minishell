/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:30:29 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/01 15:31:53 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_word(t_data *data, int i, char c)
{
	int j;
	int z;

	j = 0;
	while (data->line[i + j] != c && data->line[i + j] != '\0')
		j++;
	data->tokens[data->word] = malloc(sizeof(char) * (j + 1));
	if (!data->tokens[data->word])
		exit(1);
	data->tokens[data->word][j] = '\0';
	z = 0;
	while (data->line[i + z] != c && data->line[i + z] != '\0')
	{
		data->tokens[data->word][z] = data->line[i + z];
		z++;
	}
	data->word++;
	return (j + 1);
}

static int	dc_case_2(t_data *data, int i)
{
	int j;

	j = 0;
	data->n_dc_2--;
	j++;
	if (data->line[i + j] == '"')
		j++;
	else
		j += save_word(data, i + j, '"');
	return (j);
}

static int	sc_case_2(t_data *data, int i)
{
	int	j;

	j = 0;
	data->n_sc_2--;
	j++;
	if (data->line[i + j] == 39)
		j++;
	else
		j += save_word(data, i + j, 39);
	return (j);
}

void	save_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == ' ')
			i++;
		else if (data->line[i] == '"')
			i += dc_case_2(data, i);
		else if (data->line[i] == 39)
			i += sc_case_2(data, i);
		else
			i += save_word(data, i, ' ');
	}
}
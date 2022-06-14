/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:31:14 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 13:41:21 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	malloc_tokens(t_data *data)
{
	int	i;

	i = token_len(data, 0);
	data->word = 0;
	while (data->word < data->count)
	{
		data->tokens[data->word] = malloc(sizeof(char) * data->len);
		if (!data->tokens[data->word])
			ft_error(data, "Failed tokens malloc :(");
		data->word++;
		i = token_len(data, i);
	}
	data->word = 0;
	return (1);
}

static int	save_tokens_dc(t_data *data, int j)
{
	data->i++;
	data->dc_2--;
	while (data->line[data->i] != 34 && data->line[data->i] != '\0')
	{
		if (data->line[data->i] == 39)
			data->sc_2--;
		if (data->line[data->i] == '$')
			j = save_env(data, j);
		else
		{
			data->tokens[data->word][j] = data->line[data->i];
			data->i++;
			j++;
		}
	}
	if (data->line[data->i] == 34)
	{
		data->dc_2--;
		data->i++;
	}
	return (j);
}

static int	save_tokens_sc(t_data *data, int j)
{
	data->i++;
	data->sc_2--;
	while (data->line[data->i] != 39 && data->line[data->i] != '\0')
	{
		if (data->line[data->i] == 34)
			data->dc_2--;
		data->tokens[data->word][j] = data->line[data->i];
		data->i++;
		j++;
	}
	if (data->line[data->i] == 39)
	{
		data->sc_2--;
		data->i++;
	}
	return (j);
}

static int	save_tokens_normal(t_data *data, int j)
{
	if (data->line[data->i] == 34)
		data->dc_2--;
	if (data->line[data->i] == 39)
		data->sc_2--;
	if (data->line[data->i] == '$')
		j = save_env(data, j);
	else
	{
		data->tokens[data->word][j] = data->line[data->i];
		data->i++;
		j++;
	}
	return (j);
}

void	save_tokens(t_data *data)
{
	int	j;

	data->tokens = (char **)malloc(sizeof(char *) * (data->count + 1));
	if (!data->tokens)
		ft_error(data, "Failed token malloc :(");
	data->tokens[data->count] = 0;
	malloc_tokens(data);
	while (data->line[data->i] != '\0')
	{
		j = 0;
		while (data->line[data->i] != ' ' && data->line[data->i] != '\0')
		{
			if (data->line[data->i] == 34 && data->dc_2 > 1)
				j = save_tokens_dc(data, j);
			else if (data->line[data->i] == 39 && data->sc_2 > 1)
				j = save_tokens_sc(data, j);
			else
				j = save_tokens_normal(data, j);
		}
		data->tokens[data->word][j] = '\0';
		if (data->line[data->i] == ' ')
			data->i++;
		data->word++;
	}
}

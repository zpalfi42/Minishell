/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:30:29 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/02 15:42:35 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_len(t_data *data, int i, char c)
{
	int	j;

	j = 0;
	while (data->line[i + j] != c && data->line[i + j] != '\0')
		j++;
	return (j);
}

static int	word_len_2(t_data *data, int i, char c)
{
	int	j;

	j = 0;
	while (data->line[i + j] != c && data->line[i + j] != '\0')
	{
		if (data->line[i + j] == 34 && data->dc_2 > 1)
		{
			j += word_len(data, i + j, 34);
		}
		j++;
	}
	return (j);
}

static int	save_word(t_data *data, int i, char c)
{
	int j;

	data->tokens[data->word] = (char *)malloc(sizeof(char) * (word_len(data, i, c) + 1));
	if (!data->tokens[data->word])
		exit(1);
	data->tokens[data->word][word_len(data, i, c)] = '\0';
	j = 0;
	while (data->line[i + j] != c && data->line[i + j] != '\0')
	{
		data->tokens[data->word][j] = data->line[i + j];
		j++;
	}
	data->word++;
	return (word_len(data, i, c) + 1);
}

static int	save_word_2(t_data *data, int i, char c)
{
	int j;
	int	aux;

	data->tokens[data->word] = (char *)malloc(sizeof(char) * (word_len_2(data, i, c) + 1));
	if (!data->tokens[data->word])
		exit(1);
	data->tokens[data->word][word_len(data, i, c)] = '\0';
	j = 0;
	aux = 0;
	while (data->line[i + j] != c && data->line[i + j] != '\0')
	{
		printf("AAAAAA %c\n", data->line[i + j]);
		if (data->line[i + j] == 34 && data->dc_2 > 1)
		{
			j++;
			aux++;
			while (data->line[i + j] != 34 && data->line[i + j] != '\0')
			{
				//printf("ZzzzzZZ\n");
				data->tokens[data->word][j - aux] = data->line[i + j];
				j++;
			}
			j++;
		}
		else
		{
			data->tokens[data->word][j - aux] = data->line[i + j];
			j++;
		}
	}
	data->word++;
	return (word_len_2(data, i, c) + 1);
}

static int	dc(t_data *data, int i)
{
	int j;

	j = 1;
	data->dc_2--;
	if (data->line[i + j] == 34)
		j++;
	else
		j += save_word(data, i + j, 34);
	return (j);
}

static int	sc(t_data *data, int i)
{
	int	j;

	j = 1;
	data->sc_2--;
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
	printf("GSJUGIS%d\n", data->count);
	while (data->line[i] != '\0' && data->word < data->count)
	{
		if (data->line[i] == ' ')
			i++;
		else if (data->line[i] == 34)
			i += dc(data, i);
		else if (data->line[i] == 39)
			i += sc(data, i);
		else
			i += save_word_2(data, i, ' ');
	}
}
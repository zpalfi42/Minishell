/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:31:14 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:56:50 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* malloc_tokens() with help of token_len() mallocs the right amount of space
* needed for every token.
*/

int	malloc_tokens(t_data *data)
{
	int	i;

	i = token_len(data, 0);
	data->word = 0;
	while (data->word < data->count)
	{
		data->tokens[data->word] = malloc(sizeof(char) * (data->len + 1));
		if (!data->tokens[data->word])
			ft_error(data, "Failed tokens malloc :(");
		data->word++;
		i = token_len(data, i);
		if (i == -1)
			break ;
	}
	data->word = 0;
	return (1);
}

/*
* save_tokens_dc() saves the tokens that are between dquotes. If a $ is
* found, it expands to the enviorment variable it refers too.
*/

static int	save_tokens_dc(t_data *data, int j)
{
	data->i++;
	data->dc_2--;
	while (data->line[data->i] != 34 && data->line[data->i] != '\0')
	{
		if (data->line[data->i] == 39)
			data->sc_2--;
		if (data->line[data->i] == '$' && data->line[data->i + 1] != '\0'
			&& data->line[data->i + 1] != ' ' && data->line[data->i + 1] != '"')
		{
			if (data->line[data->i + 1] == '?')
				j = expand_errno(data, j);
			else
				j = expand_env_var(data, j);
		}
		else
			data->tokens[data->word][j++] = data->line[data->i++];
	}
	if (data->line[data->i] == 34)
	{
		data->dc_2--;
		data->i++;
	}
	return (data->tokens_type[data->word] = 2, j);
}

/*
* save_tokens_sc() saves the tokens that are between squotes.
*/

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
	data->tokens_type[data->word] = 1;
	return (j);
}

/*
* save_tokens_normal() ves the tokens that are between spaces not quotes.
* if a $ is found, it will expand to the enviroment variable it refers too.
*/

static int	save_tokens_normal(t_data *data, int j)
{
	if (data->line[data->i] == 34)
		data->dc_2--;
	if (data->line[data->i] == 39)
		data->sc_2--;
	if (data->line[data->i] == '$' && data->line[data->i + 1] != '\0'
		&& data->line[data->i + 1] != ' ')
	{
		if (data->line[data->i + 1] == '?')
			j = expand_errno(data, j);
		else
			j = expand_env_var(data, j);
	}
	else
	{
		data->tokens[data->word][j] = data->line[data->i];
		data->i++;
		j++;
	}
	data->tokens_type[data->word] = 0;
	return (j);
}

/*
* save_tokens() parses data->line saving all the tokens that data->line
* contains. If a dquote is found save_tokens_dc() is called, if a squote
* is found instead save_tokens_sc() is called, else save_tokens_normal called.
*/

void	save_tokens(t_data *data)
{
	int	j;

	save_tokens_init(data);
	while (data->line[data->i] != '\0')
	{
		j = 0;
		while (data->line[data->i] == ' ' && data->line[data->i] != '\0')
			data->i++;
		if (data->line[data->i] == '\0')
			break ;
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
		data->word++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:30:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:58:18 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
* token_len_dc() returns the number of characters before the other dquote.
*/

static int	token_len_dc(t_data *data, int i)
{
	i++;
	data->dc--;
	while (data->line[i] != 34 && data->line[i] != '\0')
	{
		if (data->line[i] == '$' && data->line[i + 1] != '\0'
			&& data->line[i + 1] != '"')
			i = token_len_env(data, i, 0);
		else
		{
			i++;
			data->len++;
		}
	}
	if (data->line[i] == 34)
	{
		data->dc--;
		i++;
	}
	return (i);
}

/*
* token_len_sc() returns the number of characters before the other squote.
*/

static int	token_len_sc(t_data *data, int i)
{
	i++;
	data->sc--;
	while (data->line[i] != 39 && data->line[i] != '\0')
	{
		i++;
		data->len++;
	}
	if (data->line[i] == 39)
	{
		data->sc--;
		i++;
	}
	return (i);
}

/*
* token_len_env() searches for the env variable in envp and count how
* many character the value is and returns it.
*/

int	token_len_env(t_data *data, int i, int j)
{
	char	*name;
	char	*envp_name;
	int		z;

	i++;
	while (is_valid_name(data->line[i + j], j))
		j++;
	name = malloc(sizeof(char) * (j + 1));
	if (!name)
		ft_error(data, "Failed malloc :(");
	j = -1;
	while ((++j > -42) && is_valid_name(data->line[i + j], j))
		name[j] = data->line[i + j];
	name[j] = '\0';
	z = -1;
	while (data->envp[++z] != 0)
	{
		envp_name = export_name(data, data->envp[z]);
		if (ft_strcmp(envp_name, name))
			data->len += ft_strlen(export_value(data, data->envp[z]));
		free(envp_name);
	}
	free(name);
	return (i + j);
}

/*
* prove_in_line() checks if i is inside line.
*/

int	prove_in_line(t_data *data, int i, int mode)
{
	int	j;

	j = -1;
	while (data->line[++j] != '\0')
	{
		if (i == j)
			break ;
	}
	if (mode == 0)
		token_len_init(data);
	return (j);
}

/*
* token_len() parses data->line from i until the token finishes, then
* returns the large of the tokens to do the right malloc. If a $ is found
* len_env() is called, if a dquote found token_len_dc() called, else if
* squote is found token_len_sc() called, else data_len_up() called.
*/

int	token_len(t_data *data, int i)
{
	int	j;

	j = prove_in_line(data, i, 0);
	while ((data->line) && data->line[j] != '\0')
	{
		while (data->line[j] == ' ' && data->line[j] != '\0')
			j++;
		while (data->line[j] != '\0' && data->line[j] != ' ')
		{
			if (data->line[j] != '\0' && data->line[j] == '$')
				j = prove_in_line(data, len_env(data, j), 1);
			if (data->line[j] != '\0' && data->line[j] == 34 && data->dc > 1)
				j = prove_in_line(data, token_len_dc(data, j), 1);
			else if (data->line[j] == 39 && data->sc > 1)
				j = prove_in_line(data, token_len_sc(data, j), 1);
			else
			{
				j += data_len_up(data);
			}
		}
		j = prove_in_line(data, j, 1);
		if (data->line[j] == '\0' || data->line[j] == ' ')
			break ;
	}
	return (data->len++, j + 1);
}

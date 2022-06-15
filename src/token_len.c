/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:30:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/15 15:04:19 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	token_len_env(t_data *data, int i, int j)
// {
// 	char	*name;
// 	t_list	*envo;

// 	i++;
// 	while (is_valid_name(data->line[i + j]))
// 		j++;
// 	name = malloc(sizeof(char) * j);
// 	if (!name)
// 		ft_error(data, "Failed malloc :(");
// 	j = 0;
// 	while (is_valid_name(data->line[i + j]))
// 	{
// 		name[j] = data->line[i + j];
// 		j++;
// 	}
// 	name[j] = '\0';
// 	envo = data->env;
// 	while (data->env)
// 	{
// 		if (ft_strcmp(data->env->name, name))
// 			data->len += ft_strlen(data->env->value);
// 		data->env = data->env->next;
// 	}
// 	data->env = envo;
// 	free(name);
// 	return (i + j);
// }

static int	token_len_dc(t_data *data, int i)
{
	i++;
	data->dc--;
	while (data->line[i] != 34 && data->line[i] != '\0')
	{
		// if (data->line[i] == '$')
			// i = token_len_env(data, i, 0);
		// else
		// {
			i++;
			data->len++;
		// }
	}
	if (data->line[i] == 34)
	{
		data->dc--;
		i++;
	}
	return (i);
}

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

int	token_len(t_data *data, int i)
{
	data->len = 0;
	data->dc = data->dc_2;
	data->sc = data->sc_2;
	while (data->line[i] != '\0')
	{
		while (data->line[i] != ' ' && data->line[i] != '\0')
		{
			// if (data->line[i] == '$')
				// i = token_len_env(data, i, 0);
			if (data->line[i] == 34 && data->dc > 1)
				i = token_len_dc(data, i);
			else if (data->line[i] == 39 && data->sc > 1)
				i = token_len_sc(data, i);
			else
			{
				data->len++;
				i++;
			}
		}
		if (data->line[i] == ' ' || data->line[i] == '\0')
			break ;
	}
	data->len++;
	return (i + 1);
}

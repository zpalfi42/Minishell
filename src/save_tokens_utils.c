/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:39:27 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 16:42:20 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(char c)
{
	if ((47 < c && c < 58) || (64 < c && c < 91)
		|| (96 < c && c < 123) || (c == 95))
		return (1);
	return (0);
}

int	save_env_2(t_data *data, int j, char *name)
{
	int	z;

	z = 0;
	while (data->env)
	{
		if (ft_strcmp(data->env->name, name))
		{
			while (data->env->value[z])
			{
				data->tokens[data->word][j] = data->env->value[z];
				z++;
				j++;
			}
		}
		data->env = data->env->next;
	}
	return (j);
}

int	save_env(t_data *data, int j)
{
	int		z;
	char	*name;
	t_list	*envo;

	envo = data->env;
	data->i++;
	z = 0;
	while (is_valid_name(data->line[data->i + z]))
		z++;
	name = malloc(sizeof(char) * z);
	if (!name)
		ft_error(data, "Failed malloc :(");
	z = 0;
	while (is_valid_name(data->line[data->i]))
	{
		name[z] = data->line[data->i];
		z++;
		data->i++;
	}
	name[z] = '\0';
	j = save_env_2(data, j, name);
	data->env = envo;
	free(name);
	return (j);
}

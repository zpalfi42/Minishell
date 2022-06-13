/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:50 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/13 15:48:35 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_name(t_data *data)
{
	char	*ret;
	int		i;

	i = 0;
	while (data->tokens[1][i] != '=')
		i++;
	ret = malloc(sizeof(char) * i);
	i = 0;
	while (data->tokens[1][i] != '=')
	{
		ret[i] = data->tokens[1][i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*export_value(t_data *data)
{
	char	*ret;
	int		i;

	i = 0;
	while (data->tokens[1][i] != '=')
		i++;
	i++;
	int j = 0;
	while (data->tokens[1][i + j] != '\0')
		j++;
	ret = malloc(sizeof(char) * j);
	j = 0;
	while (data->tokens[1][i + j] != '\0')
	{
		ret[j] = data->tokens[1][i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	valid_export(t_data *data)
{
	int	i;
	int	aux;

	i = 1;
	while(data->tokens[1][i])
	{
		if (data->tokens[1][i] == '=' && i != 0)
			aux = 0;
		i++;
	}
	return (aux);
}

void	change_value(t_data *data)
{
	char	*name;
	t_list	*envo;

	name = export_name(data);
	envo = data->env;
	while (data->env)
	{
		if (ft_strcmp(data->env->name, name))
			break ;
		data->env = data->env->next;
	}
	free(data->env->value);
	data->env->value = export_value(data);
	data->env = envo;
	free(name);
}

int	export_exists(t_data *data)
{
	char	*name;
	int		aux;
	t_list	*envo;

	aux = 0;
	envo = data->env;
	name = export_name(data);
	while (data->env)
	{
		if (ft_strcmp(data->env->name, name))
		{
			if (data->env->mode == 0)
			{
				printf("\033[1;31mCan't change %s value!\n", data->env->name);
				aux = 2;
			}
			else
				aux = 1;
			break ;
		}
		data->env = data->env->next;
	}
	data->env = envo;
	free(name);
	return (aux);
}
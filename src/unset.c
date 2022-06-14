/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:35:19 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 14:22:18 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_one_env(t_data *data)
{
	t_list	*aux;

	aux = data->env->next;
	data->env->next = data->env->next->next;
	free(aux->name);
	free(aux->value);
	free(aux);
}

static int	unset_pars(t_data *data, char *name)
{
	while (data->env && data->env->next)
	{
		if (ft_strcmp(data->env->next->name, name))
		{
			if (data->env->next->mode == 1)
				del_one_env(data);
			else
				printf("\033[1;31mCan't delete %s!\n", data->env->next->name);
			return (1);
		}
		data->env = data->env->next;
	}
	return (0);
}

void	do_unset(t_data *data)
{
	char	*name;
	t_list	*envo;
	int		i;

	(void) data;
	name = data->tokens[1];
	envo = data->env;
	i = 0;
	if (ft_strcmp(data->env->name, name))
	{
		if (data->env->next->mode == 1)
			del_one_env(data);
		else
			printf("\033[1;31mCan't delete %s!\n", data->env->name);
		i = 1;
	}
	else
		i = unset_pars(data, name);
	if (i == 0)
		printf("\033[1;31m%s does not exist!\n", name);
	data->env = envo;
}

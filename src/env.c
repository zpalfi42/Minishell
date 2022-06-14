/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:59:29 by ealonso-          #+#    #+#             */
/*   Updated: 2022/06/14 14:23:06 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_env(t_data *data)
{
	t_list	*envo;

	envo = data->env;
	while (data->env)
	{
		printf("%s=%s\n", data->env->name, data->env->value);
		data->env = data->env->next;
	}
	data->env = envo;
}

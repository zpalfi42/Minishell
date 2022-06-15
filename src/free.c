/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:49:44 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/15 15:01:43 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	del_actual_env(t_data *data)
// {
// 	free(data->env->name);
// 	free(data->env->value);
// 	free(data->env);
// }

// void	clear_env(t_data *data)
// {
// 	t_list	*t;

// 	while (data->env && data->env->next)
// 	{
// 		printf("%s\n", data->env->name);
// 		t = data->env->next;
// 		del_actual_env(data);
// 		data->env = t;
// 	}
// }

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->line != 0)
	{
		while (data->tokens[i] != 0)
		{
			free(data->tokens[i]);
			i++;
		}
		free(data->tokens);
	}
}

void	free_exit(t_data *data)
{
	free_all(data);
	// clear_env(data);
	free(data);
}

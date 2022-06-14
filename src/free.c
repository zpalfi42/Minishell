/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:49:44 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 14:22:52 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_data *data)
{
	t_list	*t;

	while (data->env)
	{
		t = data->env->next;
		del_one_env(data);
		data->env = t;
	}
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		if (data->tokens[i])
			free(data->tokens[i]);
		i++;
	}
	if (data->tokens[i])
		free(data->tokens[i]);
	free(data->tokens);
	if (data->ast->dir)
		free(data->ast->dir);
	if (data->ast)
		free(data->ast);
}

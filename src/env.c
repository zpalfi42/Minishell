/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:59:29 by ealonso-          #+#    #+#             */
/*   Updated: 2022/06/21 15:44:04 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->tokens[1] != 0)
	{
		printf("Error: %s\n", strerror(2));
		data->erno = 2;
	}
	else
	{
		while (data->envp[i])
		{
			printf("%s\n", data->envp[i]);
			i++;
		}
	}
}

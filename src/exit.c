/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:38:08 by ealonso-          #+#    #+#             */
/*   Updated: 2022/06/21 14:31:29 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_data *data)
{
	int	i;
	int	aux;

	i = -1;
	aux = 0;
	if (data->tokens[1] != 0)
	{
		while (data->tokens[1][++i])
			if (!ft_isdigit(data->tokens[1][i]))
				aux = 1;
		if (aux == 0)
			data->erno = ft_atoi(data->tokens[1]);
	}
	printf("Exit");
	free_exit(data);
	exit (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:38:08 by ealonso-          #+#    #+#             */
/*   Updated: 2022/07/20 16:49:12 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_exit(t_data *data, t_cmd *cmd, int mode)
{
	int	i;
	int	aux;

	i = -1;
	aux = 0;
	if (cmd->tokens[1] != 0)
	{
		while (cmd->tokens[1][++i])
			if (!ft_isdigit(cmd->tokens[1][i]))
				aux = 1;
		if (aux == 0)
			data->erno = ft_atoi(cmd->tokens[1]);
	}
	if (mode != 1)
	{
		printf("Exit");
		free_exit(data);
	}
	exit (1);
	return (1);
}

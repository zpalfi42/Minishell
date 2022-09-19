/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:38:08 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/15 15:53:57 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	exit_control(t_cmd *cmd, int aux, int i)
{
	aux = 0;
	i = 0;
	if (cmd->tokens[2] != 0)
	{
		ft_putstr_fd("exit: too many arguments\n", 1);
		g_status = 1;
	}
	else
	{
		while (cmd->tokens[1][i] == ' ')
			i++;
		if (cmd->tokens[1][i] == '-' || cmd->tokens[1][i] == '+')
			i++;
		while (cmd->tokens[1][i])
		{
			if (!ft_isdigit(cmd->tokens[1][i]))
				aux = 1;
			i++;
		}
		if (aux == 0)
			g_status = ft_atoi(cmd->tokens[1]);
	}
	return (aux);
}

int	do_exit(t_data *data, t_cmd *cmd, int mode)
{
	int	aux;

	aux = 0;
	if (cmd->tokens[1] != 0)
		aux = exit_control(cmd, 0, 0);
	if (mode != 1)
	{
		printf("Exit");
		if (aux == 1)
		{
			g_status = 255;
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->tokens[1], 1);
			ft_putstr_fd(": numeric argument requiered\n", 2);
		}
		free_exit(data);
	}
	exit (g_status);
	return (1);
}

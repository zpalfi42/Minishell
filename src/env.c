/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:59:29 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/15 12:05:04 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	do_env(t_data *data, t_cmd *cmd, int fd, int mode)
{
	int	i;

	i = 0;
	if (cmd->tokens[1] != 0)
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(cmd->tokens[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		g_status = 1;
		if (mode == 1)
			exit(g_status);
	}
	else
	{
		while (data->envp[i])
		{
			ft_putendl_fd(data->envp[i], fd);
			i++;
		}
		g_status = 0;
	}
	if (mode == 1)
		exit (g_status);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:58:44 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 14:09:56 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	do_dir(t_data *data, t_cmd *cmd, int mode)
{
	(void) data;
	if (cmd->cmd[1] == '\0')
	{
		ft_putstr_fd("/: is a directory\n", 1);
		g_status = 126;
		if (mode == 1)
			exit(g_status);
	}
	else
	{
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_status = 127;
		if (mode == 1)
			exit(g_status);
	}
}

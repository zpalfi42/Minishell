/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:06:53 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/14 13:15:16 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	do_path_cmd(t_data *data, t_cmd *cmd)
{
	if (access(cmd->cmd, 0) == 0)
		execve(cmd->cmd, cmd->tokens, data->envp);
	else
	{
		perror("Error");
		g_status = errno;
		exit(g_status);
	}
}

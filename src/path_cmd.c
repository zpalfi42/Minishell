/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:06:53 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/20 16:49:21 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_path_cmd(t_data *data, t_cmd *cmd)
{
	if (access(cmd->cmd, 0) == 0)
		execve(cmd->cmd, cmd->tokens, data->envp);
	else
	{
		perror("Error");
		data->erno = errno;
		exit(data->erno);
	}
}

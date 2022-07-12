/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:59:29 by ealonso-          #+#    #+#             */
/*   Updated: 2022/07/12 16:41:36 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_env(t_data *data, t_cmd *cmd, int fd, int mode)
{
	int	i;

	i = 0;
	if (cmd->tokens[1] != 0)
	{
		printf("Error: %s\n", strerror(2));
		data->erno = 2;
	}
	else
	{
		while (data->envp[i])
		{
			ft_putendl_fd(data->envp[i], fd);
			i++;
		}
	}
	if (mode == 1)
		exit (1);
	return (1);
}

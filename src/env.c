/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:59:29 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/12 13:41:26 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_env(t_data *data, t_cmd *cmd, int fd, int mode)
{
	int	i;

	i = 0;
	if (cmd->tokens[1] != 0)
	{
		printf("Error: %s\n", strerror(1));
		data->erno = 1;
		if (mode == 1)
			exit(data->erno);
	}
	else
	{
		while (data->envp[i])
		{
			ft_putendl_fd(data->envp[i], fd);
			i++;
		}
		data->erno = 0;
	}
	if (mode == 1)
		exit (0);
	return (1);
}

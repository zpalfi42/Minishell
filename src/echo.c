/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:34:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/04 14:30:36 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_cmd *cmd, int i, int n, int fd)
{
	while (cmd->tokens[i] != 0)
	{
		if (cmd->tokens[i + 1] != 0)
		{
			ft_putstr_fd(cmd->tokens[i], fd);
			ft_putstr_fd(" ", fd);
		}
		else
			ft_putstr_fd(cmd->tokens[i], fd);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", fd);
}

int	do_echo(t_cmd *cmd, int fd)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (cmd->tokens[i] == 0)
		ft_putstr_fd("\n", fd);
	else if (ft_strcmp(cmd->tokens[i], "-n\0"))
	{
		n = 1;
		i++;
	}
	else
		print_echo(cmd, i, n, fd);
	return (1);
}

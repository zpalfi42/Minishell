/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:34:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/22 17:37:14 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_cmd *cmd, int i, int n)
{
	while (cmd->tokens[i] != 0)
	{
		if (cmd->tokens[i + 1] != 0)
			printf("%s ", cmd->tokens[i]);
		else
			printf("%s", cmd->tokens[i]);
		i++;
	}
	if (!n)
		printf("\n");
}

void	do_echo(t_cmd *cmd)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (cmd->tokens[i] == 0)
		printf("\n");
	else if (ft_strcmp(cmd->tokens[i], "-n\0"))
	{
		n = 1;
		i++;
	}
	else
		print_echo(cmd, i, n);
}

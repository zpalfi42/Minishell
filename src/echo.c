/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:34:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/13 16:30:37 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_data *data, int i, int n)
{
	while (data->tokens[i] != 0)
	{
		if (data->tokens[i + 1] != 0)
			printf("%s ", data->tokens[i]);
		else
			printf("%s", data->tokens[i]);
		i++;
	}
	if (!n)
		printf("\n");
}

void	do_echo(t_data *data, t_ast *ast)
{
	int	n;
	int	i;

	(void) ast;
	n = 0;
	i = 1;
	if (data->tokens[i] == 0)
		printf("\n");
	else if (ft_strcmp(data->tokens[i], "-n\0"))
	{
		n = 1;
		i++;
	}
	else
		print_echo(data, i, n);
}

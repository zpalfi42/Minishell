/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:34:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/08 15:35:56 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_echo(t_data *data, t_ast *ast)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	ast->nr = 1;
	if (ft_strncmp(data->tokens[i], "-n\0", 3) == 0)
	{
		n = 1;
		i++;
	}
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

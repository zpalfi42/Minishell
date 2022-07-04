/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:38:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/28 17:29:29 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_parser(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->pipes = 0;
	while (data->tokens[++i] != 0)
	{
		if (ft_strcmp(data->tokens[i], "|\0"))
			data->pipes++;
	}
	i = -1;
	while (data->tokens[++i] != 0)
		if (ft_strcmp(data->tokens[i], "|\0"))
			break ;
	data->cmd_lst = cmd_lst_new(data->tokens, 0, i);
	while (data->pipes > 0)
	{
		j = i + 1;
		while (data->tokens[++i] != 0)
			if (ft_strcmp(data->tokens[i], "|\0"))
				break ;
		cmd_add_back(&data->cmd_lst, cmd_lst_new(data->tokens, j, i));
		data->pipes--;
	}
}

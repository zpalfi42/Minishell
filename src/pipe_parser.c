/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:38:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/26 15:29:01 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_parser_2(t_data *data, int i)
{
	int	j;

	while (data->pipes > 0)
	{
		data->z = 0;
		j = i + 1;
		while (data->tokens[++i] != 0)
			if (ft_strcmp(data->tokens[i], "|\0"))
				break ;
		if (data->tokens[i] != 0 && ft_strcmp(data->tokens[i + 1], "|\0"))
		{
			printf("zsh: parse error near '%s'\n", data->tokens[i]);
			return (-1);
		}
		if (cmd_add_back(&data->cmd_lst,
				cmd_lst_new(data, data->tokens, j, i)) == -1)
			return (-1);
		data->pipes--;
	}
	return (0);
}

int	pipe_parser(t_data *data)
{
	int	i;

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
	if (i == 0 || (data->tokens[i] != 0
			&& ft_strcmp(data->tokens[i + 1], "|\0")))
	{
		printf("zsh: parse error near '%s'\n", data->tokens[i]);
		return (-1);
	}
	data->cmd_lst = cmd_lst_new(data, data->tokens, 0, i);
	if (data->cmd_lst == NULL)
		return (-1);
	return (pipe_parser_2(data, i));
}

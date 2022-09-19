/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:12:44 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:54:28 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* cmd_tokens_saver() saves all the tokens and tokens_type
* inside the t_cmd *n struct.
*/

void	cmd_tokens_saver(t_cmd *n, t_data *data, int i, int j)
{
	int	z;

	z = 0;
	n->tokens[z] = data->tokens[i];
	n->tokens_type[z] = data->tokens_type[i];
	i++;
	while (data->tokens[i] != 0 && i < j)
	{
		if ((data->tokens[i][0] == '<' || data->tokens[i][0] == '>')
			&& data->tokens_type[i] == 0)
			i += redir_type(data->tokens, i);
		else
		{
			n->arg[z] = data->tokens[i];
			n->tokens[z + 1] = data->tokens[i];
			n->tokens_type[z + 1] = data->tokens_type[i];
			z++;
			i++;
		}
	}
	n->arg[z] = 0;
	n->tokens[z + 1] = 0;
	n->tokens_type[z + 1] = -1;
}

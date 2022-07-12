/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:58:21 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/12 16:41:48 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env(t_data *data, int i)
{
	if (data->line[i + 1] == '?')
		i = token_len_errno(data, i);
	else
		i = token_len_env(data, i, 0);
	return (i);
}

void	token_len_init(t_data *data)
{
	data->len = 0;
	data->dc = data->dc_2;
	data->sc = data->sc_2;
}

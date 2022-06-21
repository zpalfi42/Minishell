/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:58:21 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/21 16:03:49 by zpalfi           ###   ########.fr       */
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

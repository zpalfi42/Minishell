/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tokens_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:49:50 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:55:49 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* save_tokens_init() malloc the number of tokens inside 
* data->tokens && data->token_type. Then calls malloc_tokens().
*/

void	save_tokens_init(t_data *data)
{
	data->tokens = (char **)malloc(sizeof(char *) * (data->count + 1));
	data->tokens_type = (int *)malloc(sizeof(int) * (data->count + 1));
	if (!data->tokens || !data->tokens_type)
		ft_error(data, "Failed token malloc :(");
	data->tokens[data->count] = 0;
	data->tokens_type[data->count] = -1;
	malloc_tokens(data);
}

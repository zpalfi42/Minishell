/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:49:44 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/08 16:41:37 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		if (data->tokens[i])
			free(data->tokens[i]);
		i++;
	}
	if (data->tokens[i])
		free(data->tokens[i]);
	free(data->tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/13 16:35:42 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(t_data *data, t_ast *ast)
{
	int	i;

	(void) ast;
	if (valid_export(data))
	{
		printf("\033[1;31mInvalid export!\n");
	}
	else
	{
		i = export_exists(data);
		if (i == 1)
			change_value(data);
		else if (i == 0)
			ft_lstadd_back(&data->env, ft_lstnew(export_name(data),
					export_value(data), 1));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:31:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 14:23:10 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_home(t_data *data)
{
	int		i;
	int		j;
	int		z;

	i = 0;
	j = 0;
	data->ast->dir = malloc(sizeof(char) * 200);
	while (data->tokens[1][i] != '\0')
	{
		if (data->tokens[1][i] == '~')
		{
			z = 0;
			while (data->ast->home[z])
				data->ast->dir[j++] = data->ast->home[z++];
			i++;
		}
		else
			data->ast->dir[j++] = data->tokens[1][i++];
	}
}

void	do_cd(t_data *data)
{
	if (data->tokens[1] != 0)
		replace_home(data);
	if (data->tokens[1] == 0)
	{
		if (chdir(data->ast->home) != 0)
			perror("cd");
	}
	else if (chdir(data->ast->dir) != 0)
	{
		perror("cd");
	}
}

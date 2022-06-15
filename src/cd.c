/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:31:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/15 17:14:19 by zpalfi           ###   ########.fr       */
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
	data->dir = malloc(sizeof(char) * 200);
	if (!data->dir)
		ft_error(data, "Failed malloc :(");
	while (data->tokens[1][i] != '\0')
	{
		if (data->tokens[1][i] == '~')
		{
			z = 0;
			while (data->home[z])
				data->dir[j++] = data->home[z++];
			i++;
		}
		else
			data->dir[j++] = data->tokens[1][i++];
	}
}

void	do_cd(t_data *data)
{
	if (data->tokens[1] != 0)
		replace_home(data);
	if (data->tokens[1] == 0)
	{
		if (chdir(data->home) != 0)
			perror("cd");
	}
	else if (chdir(data->dir) != 0)
	{
		perror("cd");
	}
	else
		free(data->dir);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:31:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/13 16:34:55 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_home(t_data *data, t_ast *ast)
{
	int		i;
	int		j;
	int		z;

	i = 0;
	j = 0;
	ast->dir = malloc(sizeof(char) * 200);
	while (data->tokens[1][i] != '\0')
	{
		if (data->tokens[1][i] == '~')
		{
			z = 0;
			while (ast->home[z])
				ast->dir[j++] = ast->home[z++];
			i++;
		}
		else
			ast->dir[j++] = data->tokens[1][i++];
	}
}

void	do_cd(t_data *data, t_ast *ast)
{
	if (data->tokens[1] != 0)
		replace_home(data, ast);
	if (data->tokens[1] == 0)
	{
		if (chdir(ast->home) != 0)
			perror("cd");
	}
	else if (chdir(ast->dir) != 0)
	{
		perror("cd");
	}
}

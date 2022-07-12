/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:30:19 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/12 15:23:24 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_home(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	int		z;

	i = 0;
	j = 0;
	data->dir = malloc(sizeof(char) * 200);
	if (!data->dir)
		ft_error(data, "Failed malloc :(");
	while (cmd->tokens[1][i] != '\0')
	{
		if (cmd->tokens[1][i] == '~')
		{
			z = 0;
			while (data->home[z])
				data->dir[j++] = data->home[z++];
			i++;
		}
		else
			data->dir[j++] = cmd->tokens[1][i++];
	}
}

char	*cd_init(t_data *data)
{
	char	*pwd;
	char	*oldpwd;

	pwd = malloc(sizeof(char) * 200);
	if (!pwd)
		ft_error(data, "Failed malloc :(");
	oldpwd = malloc(sizeof(char) * 200);
	if (!pwd)
		ft_error(data, "Failed malloc :(");
	getcwd(oldpwd, 199);
	change_pwd(data, oldpwd, 1);
	return (pwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:30:19 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/08 17:00:06 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_home_routine(t_data *data, t_cmd *cmd)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
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

void	replace_home(t_data *data, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->home[i] != '\0')
		i++;
	while (cmd->tokens[1][j] != '\0')
		j++;
	data->dir = malloc(sizeof(char) * (i + j + 1));
	if (!data->dir)
		ft_error(data, "Failed malloc :(");
	replace_home_routine(data, cmd);
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

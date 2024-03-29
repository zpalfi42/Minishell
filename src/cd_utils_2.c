/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:45:44 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/15 14:06:31 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_j(t_data *data, int mode)
{
	int	j;

	j = -1;
	while (data->envp[++j])
	{
		if (mode == 0)
		{
			if (ft_strncmp(data->envp[j], "PWD=", 4) == 0)
				break ;
		}
		else
		{
			if (ft_strncmp(data->envp[j], "OLDPWD=", 7) == 0)
				break ;
		}
	}
	return (j);
}

static int	pwd_or_oldpwd(int index, char **new_envp, char *pwd, int mode)
{
	if (mode == 0)
	{
		new_envp[index] = malloc(sizeof(char) * (5 + ft_strlen(pwd)));
		new_envp[index][0] = 'P';
		new_envp[index][1] = 'W';
		new_envp[index][2] = 'D';
		new_envp[index][3] = '=';
		return (4);
	}
	else
	{
		new_envp[index] = malloc(sizeof(char) * (8 + ft_strlen(pwd)));
		new_envp[index][0] = 'O';
		new_envp[index][1] = 'L';
		new_envp[index][2] = 'D';
		new_envp[index][3] = 'P';
		new_envp[index][4] = 'W';
		new_envp[index][5] = 'D';
		new_envp[index][6] = '=';
		return (7);
	}
}

void	change_pwd_value(int index, char **new_envp, char *pwd, int mode)
{
	int		i;
	int		j;

	i = pwd_or_oldpwd(index, new_envp, pwd, mode);
	j = -1;
	while (pwd[++j] != '\0')
	{
		new_envp[index][i] = pwd[j];
		i++;
	}
	free(pwd);
	new_envp[index][i] = '\0';
}

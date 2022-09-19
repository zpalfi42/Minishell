/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:30:19 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 11:49:07 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

// That functi'on refresh the new pwd in envp.

int	replace_home(t_data *data, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strncmp(cmd->tokens[1], "-\0", 2) == 0)
		return (cd_oldpwd(data));
	else
	{
		while (data->home[i] != '\0')
			i++;
		while (cmd->tokens[1][j] != '\0')
			j++;
		data->dir = malloc(sizeof(char) * (i + j + 1));
		if (!data->dir)
			ft_error(data, "Failed malloc :(");
		replace_home_routine(data, cmd);
	}
	return (0);
}

void	change_pwd(t_data *data, char *pwd, int mode)
{
	char	**new_envp;
	int		i;
	int		j;

	j = find_j(data, mode);
	i = 0;
	while (data->envp[i] != 0)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (data->envp[++i] != 0)
	{
		if (j == i)
			change_pwd_value(i, new_envp, pwd, mode);
		else
		{
			new_envp[i] = malloc(sizeof(char) * (ft_strlen(data->envp[i]) + 1));
			ft_strlcpy(new_envp[i], data->envp[i],
				ft_strlen(data->envp[i]) + 1);
		}
		free(data->envp[i]);
	}
	free(data->envp);
	new_envp[i] = 0;
	data->envp = new_envp;
}

//this function play when the argument after command 'cd' is '~', 
//placing home as actual directory.

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
	data->dir[j] = '\0';
}

int	cd_oldpwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[++i])
		if (ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
			break ;
	data->dir = export_value(data, data->envp[i]);
	if (data->dir[0] != '\0')
		printf("%s\n", data->dir);
	else
		ft_putstr_fd("cd: OLDPWD not set\n", 1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:31:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/11 17:34:52 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	change_pwd_value(int index, char **new_envp, char *pwd, int mode)
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
	new_envp[index][i] = '\0';
}

static int	find_j(t_data *data, int mode)
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
	}
	free(data->envp);
	new_envp[i] = 0;
	data->envp = new_envp;
}

int	do_cd(t_data *data, t_cmd *cmd)
{
	char	*pwd;

	pwd = cd_init(data);
	if (cmd->tokens[1] != 0)
		replace_home(data, cmd);
	if (cmd->tokens[1] == 0)
	{
		if (chdir(data->home) != 0)
		{
			perror("cd");
			data->erno = errno;
		}
	}
	else if (chdir(data->dir) != 0)
	{
		perror("cd");
		data->erno = errno;
	}
	else
		free(data->dir);
	getcwd(pwd, 199);
	change_pwd(data, pwd, 0);
	return (1);
}

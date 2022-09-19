/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:31:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 13:32:31 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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

void	cd_home(t_data *data, int mode)
{
	if (chdir(data->home) != 0)
	{
		perror("cd");
		g_status = errno;
		if (mode == 1)
			exit (errno);
	}	
}

void	cd_failed(int mode)
{
	perror("cd");
	g_status = errno;
	if (mode == 1)
		exit (g_status);
}

void	cd_worked(t_data *data)
{
	g_status = 0;
	free(data->dir);
}

int	do_cd(t_data *data, t_cmd *cmd, int mode)
{
	char	*pwd;
	int		i;

	i = 0;
	if (cmd->tokens[1] != 0)
		i = replace_home(data, cmd);
	pwd = cd_init(data);
	if (i == 0)
	{
		if (cmd->tokens[1] == 0)
			cd_home(data, mode);
		else if (chdir(data->dir) != 0)
			cd_failed(mode);
		else
			cd_worked(data);
	}
	else
		cd_worked(data);
	getcwd(pwd, 4096);
	change_pwd(data, pwd, 0);
	if (mode == 1)
		exit (0);
	return (1);
}

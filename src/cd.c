/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:31:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/11 16:24:16 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_pwd_value(int index, char **new_envp, char *pwd)
{
	int		i;
	int		j;

	new_envp[index] = malloc(sizeof(char) * (4 + ft_strlen(pwd)));
	new_envp[index][0] = 'P';
	new_envp[index][1] = 'W';
	new_envp[index][2] = 'D';
	new_envp[index][3] = '=';
	i = 4;
	j = -1;
	while (pwd[++j] != '\0')
	{
		new_envp[index][i] = pwd[j];
		i++;
	}
	new_envp[index][i] = '\0';
}

static int	find_j(t_data *data)
{
	int	j;

	j = -1;
	while (data->envp[++j])
		if (ft_strncmp(data->envp[j], "PWD=", 4) == 0)
			break ;
	return (j);
}

static void	change_pwd(t_data *data, char *pwd)
{
	char	**new_envp;
	int		i;
	int		j;

	j = find_j(data);
	i = 0;
	while (data->envp[i] != 0)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (data->envp[++i] != 0)
	{
		if (j == i)
			change_pwd_value(i, new_envp, pwd);
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

static void	replace_home(t_data *data, t_cmd *cmd)
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

int	do_cd(t_data *data, t_cmd *cmd)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 200);
	if (!pwd)
		ft_error(data, "Failed malloc :(");
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
	change_pwd(data, pwd);
	return (1);
}

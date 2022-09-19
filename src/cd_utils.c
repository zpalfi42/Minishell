/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:30:19 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 13:32:26 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*cd_init(t_data *data)
{
	char	*pwd;
	char	*oldpwd;

	pwd = malloc(sizeof(char) * 4097);
	if (!pwd)
		ft_error(data, "Failed malloc :(");
	oldpwd = malloc(sizeof(char) * 4097);
	if (!oldpwd)
		ft_error(data, "Failed malloc :(");
	getcwd(oldpwd, 4096);
	change_pwd(data, oldpwd, 1);
	return (pwd);
}

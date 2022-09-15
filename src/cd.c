/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:31:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 14:01:34 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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

//we crreate here mallocs for old and actual pwd with 4097 size 
//(maximal for a directory with '\0')

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

// in this function we comprove if there is an argumment after the command 
//to replace home or new directory.
// We control too if there are errors and call functions to refresh new pwd.

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

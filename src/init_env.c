/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:32:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/12 12:38:31 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	oldpwd_save(t_data *data, int i)
{
	data->envp[i] = malloc(sizeof(char) * 8);
	data->first_envp[i] = malloc(sizeof(char) * 8);
	if (!data->envp[i] || !data->first_envp[i])
		return (1);
	ft_strlcpy(data->envp[i], "OLDPWD=\0", 8);
	ft_strlcpy(data->first_envp[i], "OLDPWD=\0", 8);
	return (0);
}

int	envp_save(t_data *data, char **envp, int i)
{
	data->envp[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
	data->first_envp[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
	if (!data->envp[i] || !data->first_envp[i])
		return (1);
	ft_strlcpy(data->envp[i], envp[i], (ft_strlen(envp[i]) + 1));
	ft_strlcpy(data->first_envp[i], envp[i], (ft_strlen(envp[i]) + 1));
	return (0);
}

int	envp_init(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
		i++;
	data->envp = malloc(sizeof(char *) * (i + 1));
	data->first_envp = malloc(sizeof(char *) * (i + 1));
	if (!data->first_envp || !data->envp)
		return (1);
	i = 0;
	data->erno = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			oldpwd_save(data, i);
		else
			envp_save(data, envp, i);
		i++;
	}
	data->envp[i] = 0;
	data->first_envp[i] = 0;
	return (0);
}

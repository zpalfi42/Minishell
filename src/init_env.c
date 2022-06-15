/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:32:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/15 17:14:11 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	name_len(char **envp, int z)
{
	int	i;

	i = 0;
	while (envp[z][i])
	{
		if (envp[z][i] == '=')
			break ;
		i++;
	}
	return (i);
}

static int	value_len(char **envp, int z)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[z][i] != '=')
		i++;
	i++;
	while (envp[z][i + j] != '\0')
	{
		j++;
	}
	return (j);
}

static char	*envp_name(t_data *data, char **envp, int z)
{
	int		i;
	char	*name;

	i = 0;
	name = malloc(sizeof(char) * name_len(envp, z));
	if (!name)
		ft_error(data, "Failed malloc :(");
	while (envp[z][i])
	{
		if (envp[z][i] == '=')
			break ;
		name[i] = envp[z][i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char	*envp_value(t_data *data, char **envp, int z)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = malloc(sizeof(char) * value_len(envp, z));
	if (!value)
		ft_error(data, "Failed malloc :(");
	while (envp[z][i] != '=')
		i++;
	i++;
	while (envp[z][i + j] != '\0')
	{
		value[j] = envp[z][i + j];
		j++;
	}
	value[i] = '\0';
	return (value);
}

t_list	*init_env(t_data *data, char **envp)
{
	t_list	*env;
	int		i;

	env = ft_lstnew(envp_name(data, envp, 0), envp_value(data, envp, 0), 0);
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&env, ft_lstnew(envp_name(data, envp, i),
				envp_value(data, envp, i), 0));
		i++;
	}
	return (env);
}

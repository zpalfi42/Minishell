/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:56:34 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/08 16:57:25 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_name(t_data *data, char *env)
{
	char	*ret;
	int		i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	ret = malloc(sizeof(char) * i);
	if (!ret)
		ft_error(data, "Failed malloc :(");
	i = -1;
	while (env[++i] != '=' && env[i] != '\0')
		ret[i] = env[i];
	ret[i] = '\0';
	return (ret);
}

static int	cpy_old(t_data *data, char **new_envp)
{
	int	i;

	i = -1;
	while (data->envp[++i] != 0)
	{
		new_envp[i] = malloc(sizeof(char) * (ft_strlen(data->envp[i])));
		if (!new_envp[i])
			return (-1);
		ft_strlcpy(new_envp[i], data->envp[i], (ft_strlen(data->envp[i]) + 1));
		free(data->envp[i]);
	}
	free(data->envp);
	return (i);
}

static void	free_nv(char *name, char *value)
{
	free(name);
	free(value);
}

static int	assign_new(t_data *data, t_cmd *cmd, char **new_envp, int i)
{
	int		j;
	int		z;
	char	*name;
	char	*value;

	name = export_name(data, cmd->tokens[data->i]);
	value = export_value(data, cmd->tokens[data->i]);
	i = cpy_old(data, new_envp);
	if (i == -1)
		return (1);
	new_envp[i] = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value)));
	if (!new_envp[i])
		return (1);
	j = -1;
	while (name[++j] != '\0')
		new_envp[i][j] = name[j];
	new_envp[i][j] = '=';
	j++;
	z = -1;
	while (value[++z] != '\0')
		new_envp[i][j + z] = value[z];
	new_envp[i][j + z] = '\0';
	new_envp[i + 1] = 0;
	free_nv(name, value);
	return (0);
}

void	add_export(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (data->envp[i] != 0)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp || assign_new(data, cmd, new_envp, i))
		ft_error(data, "Failed malloc :(");
	if (new_envp == NULL)
		ft_error(data, "Failed malloc :(");
	data->envp = new_envp;
}

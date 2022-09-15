/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:15 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 15:23:57 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

//Just for print 'declare-x' in each lane of the envp, 
//when use the command export without argumments.

void	print_export(t_data *data, int fd)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putendl_fd(data->envp[i], fd);
		i++;
	}
}

//Look for the name of export already exist in the envp, 
//for a replace the value, not create a new variable.

int	export_exists(t_data *data, t_cmd *cmd)
{
	char	*name;
	char	*envp_name;
	int		i;

	name = export_name(data, cmd->tokens[data->i]);
	i = -1;
	while (data->envp[++i] != 0)
	{
		envp_name = export_name(data, data->envp[i]);
		if (ft_strcmp(envp_name, name))
		{
			i = -1;
			free(envp_name);
			break ;
		}
		free(envp_name);
	}
	free(name);
	return (i);
}

//Control the first char in the export argument is alfabetical and is not '_'.
//valid too the name (all we have before '=').

int	valid_export(t_data *data, t_cmd *cmd)
{
	int	i;
	int	aux;

	aux = 1;
	i = 0;
	if (((65 > cmd->tokens[data->i][0] || cmd->tokens[data->i][0] > 90)
		&& (97 > cmd->tokens[data->i][0] || cmd->tokens[data->i][0] > 122))
		&& cmd->tokens[data->i][0] != 95)
		return (1);
	while (cmd->tokens[data->i][++i])
	{
		if (cmd->tokens[data->i][i] == '=' && aux != 0)
			aux = 0;
		else if (is_valid_name(cmd->tokens[data->i][i], i) == 0 && aux != 0)
			return (1);
	}
	return (aux);
}

//the function save the HOME value in data.

void	save_home_data(t_data *data, int mode)
{
	int		i;
	char	*aux_name;

	i = 0;
	while (data->envp[i])
	{
		aux_name = export_name(data, data->envp[i]);
		if (ft_strcmp(aux_name, "HOME\0"))
		{
			if (mode == 0)
				free(data->home);
			data->home = export_value(data, data->envp[i]);
			free(aux_name);
			break ;
		}
		free(aux_name);
		i++;
	}
}

//do_export works sorting when we have argumments and not and control errors.

int	do_export(t_data *data, t_cmd *cmd, int mode, int fd)
{
	data->i = 0;
	if (cmd->tokens[1] == NULL)
		print_export(data, fd);
	g_status = 0;
	while (cmd->tokens[++data->i] != 0)
	{
		if (valid_export(data, cmd))
		{
			ft_putstr_fd("export: ", 1);
			ft_putstr_fd(cmd->tokens[data->i], 1);
			ft_putstr_fd(": not a valid identifier", 1);
			g_status = 1;
			if (mode == 1)
				exit (1);
		}
		else
			do_export_else(data, cmd);
	}
	save_home_data(data, 0);
	if (mode == 1)
		exit (0);
	return (1);
}

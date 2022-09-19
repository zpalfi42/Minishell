/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:34:05 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:50:36 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
* Add the rest of argumment when the 'replace_home_echo need'it.
*/

char	*modify_token(t_data *data, char *token)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (data->home[i])
		i++;
	while (token[j])
		j++;
	new = malloc(sizeof(char) * (i + j));
	i = 0;
	while (data->home[i])
	{
		new[i] = data->home[i];
		i++;
	}
	j = 0;
	while (token[++j])
	{
		new[i] = token[j];
		i++;
	}
	return (new);
}

/*
* Replace '~' for home, and attach the resto of the argumment if there is.
*/

void	replace_home_echo(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->tokens[i] != 0)
	{
		if (cmd->tokens[i][0] == '~' && cmd->tokens_type[i] == 0)
		{
			if (cmd->tokens[i][1] == '\0')
				cmd->tokens[i] = data->home;
			else if (cmd->tokens[i][1] == '/')
				cmd->tokens[i] = modify_token(data, cmd->tokens[i]);
		}
		i++;
	}
}

/*
* the last step for execute Echo function.
*/

void	print_echo(t_cmd *cmd, int i, int n, int fd)
{
	while (cmd->tokens[i] != 0)
	{
		if (cmd->tokens[i + 1] != 0)
		{
			ft_putstr_fd(cmd->tokens[i], fd);
			ft_putstr_fd(" ", fd);
		}
		else
			ft_putstr_fd(cmd->tokens[i], fd);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", fd);
}

/*
* This function call the others to print the arguments or home 
* if the argument is '~'. 
*/

int	do_echo(t_data *data, t_cmd *cmd, int fd, int mode)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (cmd->tokens[i] == 0)
		ft_putstr_fd("\n", fd);
	else
	{
		replace_home_echo(data, cmd);
		if (ft_strcmp(cmd->tokens[i], "-n\0"))
		{
			n = 1;
			i++;
		}
		print_echo(cmd, i, n, fd);
	}
	if (mode == 1)
		exit(0);
	g_status = 0;
	return (1);
}

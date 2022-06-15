/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/15 15:01:30 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_data *data)
{
	if (ft_strncmp(data->cmd, "echo\0", 5) == 0)
		do_echo(data);
	else if (ft_strncmp(data->cmd, "cd\0", 3) == 0)
		do_cd(data);
	else if (ft_strncmp(data->cmd, "pwd\0", 4) == 0)
		do_pwd(data);
	else if (ft_strncmp(data->cmd, "export\0", 7) == 0)
		do_export(data);
	// else if (ft_strncmp(data->cmd, "unset\0", 6) == 0)
	// 	do_unset(data);
	else if (ft_strncmp(data->cmd, "env\0", 4) == 0)
		do_env(data);
	else if (ft_strncmp(data->cmd, "exit\0", 5) == 0)
		do_exit(data);
	else
		printf("\033[1;31mCommand not found :(\n");
}

void	ast(t_data *data)
{
	data->cmd = data->tokens[0];
	data->home = getenv("HOME");
	check_cmd(data);
}

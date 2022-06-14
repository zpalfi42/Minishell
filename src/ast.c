/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 14:23:13 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_data *data)
{
	if (ft_strncmp(data->ast->cmd, "echo\0", 5) == 0)
		do_echo(data);
	else if (ft_strncmp(data->ast->cmd, "cd\0", 3) == 0)
		do_cd(data);
	else if (ft_strncmp(data->ast->cmd, "pwd\0", 4) == 0)
		do_pwd(data);
	else if (ft_strncmp(data->ast->cmd, "export\0", 7) == 0)
		do_export(data);
	else if (ft_strncmp(data->ast->cmd, "unset\0", 6) == 0)
		do_unset(data);
	else if (ft_strncmp(data->ast->cmd, "env\0", 4) == 0)
		do_env(data);
	else if (ft_strncmp(data->ast->cmd, "exit\0", 5) == 0)
		do_exit(data);
	else
		printf("\033[1;31mCommand not found :(\n");
}

void	ast(t_data *data)
{
	data->ast = (t_ast *)malloc(sizeof(t_ast));
	if (!data->ast)
		ft_error(data, "Failed ast malloc :(");
	data->ast->cmd = data->tokens[0];
	data->ast->home = getenv("HOME");
	check_cmd(data);
}

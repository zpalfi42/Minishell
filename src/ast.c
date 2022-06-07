/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/07 18:12:51 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_echo(t_data *data, t_ast *ast)
{
	ast->nr = 1;
	if (ft_strncmp(data->tokens[1], "-n\0", 3) == 0)
	{
		printf("%s%%\n", data->tokens[2]);
	}
	else
		printf("%s\n", data->tokens[1]);
}

void	check_cmd(t_data *data, t_ast *ast)
{
	if (ft_strncmp(ast->cmd, "echo", 4) == 0)
	{
		do_echo(data, ast);
	}
	else
		ft_error(data, "Command not found :(");
}

void	ast(t_data *data)
{
	t_ast	*ast;
	
	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		ft_error(data, "Failed ast malloc :(");
	ast->cmd = data->tokens[0];
	check_cmd(data, ast);
}
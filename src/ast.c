/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/08 16:37:40 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_data *data, t_ast *ast)
{
	if (ft_strncmp(ast->cmd, "echo\0", 5) == 0)
	{
		do_echo(data, ast);
	}
	// else if (ft_strncmp(ast->cmd, "cd\0", 3) == 0)
	// {
	// 	do_cd(data, ast);
	// }
	// else if (ft_strncmp(ast->cmd, "pwd\0", 4) == 0)
	// {
	// 	do_pwd(data, ast);
	// }
	// else if (ft_strncmp(ast->cmd, "export\0", 7) == 0)
	// {
	// 	do_export(data, ast);
	// }
	// else if (ft_strncmp(ast->cmd, "unset\0", 6) == 0)
	// {
	// 	do_unset(data, ast);
	// }
	else if (ft_strncmp(ast->cmd, "env\0", 4) == 0)
	{
		do_env(data, ast);
	}
	else if (ft_strncmp(ast->cmd, "exit\0", 5) == 0)
	{
		do_exit(data, ast);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/08 14:57:20 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_echo(t_data *data, t_ast *ast)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	ast->nr = 1;
	if (ft_strncmp(data->tokens[i], "-n\0", 3) == 0)
	{
		n = 1;
		i++;
	}
	while (data->tokens[i] != 0)
	{
		if (data->tokens[i + 1] != 0)
			printf("%s ", data->tokens[i]);
		else
			printf("%s", data->tokens[i]);
		i++;
	}
	if (!n)
		printf("\n");
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
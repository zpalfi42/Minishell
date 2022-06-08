/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/08 16:56:35 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(t_data *data, t_ast *ast)
{
	char	*pwd;

	(void) data;
	(void) ast;

	pwd = malloc(sizeof(char) * 200);
	if (getcwd(pwd, 199) == NULL)
	{
		perror("getcwd");
	}
	printf("%s\n", pwd);
}

void	replace_home(t_data *data, t_ast *ast)
{
	int		i;
	int		j;
	int		z;

	i = 0;
	j = 0;
	ast->dir = malloc(sizeof(char) * 200);
	while (data->tokens[1][i] != '\0')
	{
		if (data->tokens[1][i] == '~')
		{
			z = 0;
			while (ast->home[z])
			{
				ast->dir[j] = ast->home[z];
				j++;
				z++;
			}
			i++;
		}
		else
		{
			ast->dir[j] = data->tokens[1][i];
			j++;
			i++;
		}
	}
}

void	do_cd(t_data *data, t_ast *ast)
{
	if (data->tokens[1] != 0)
		replace_home(data, ast);
	if (data->tokens[1] == 0)
	{
		if (chdir(ast->home) != 0)
			perror("cd");
	}
	else if (chdir(ast->dir) != 0)
	{
		perror("cd");
	}
}

void	check_cmd(t_data *data, t_ast *ast)
{
	if (ft_strncmp(ast->cmd, "echo\0", 5) == 0)
	{
		do_echo(data, ast);
	}
	else if (ft_strncmp(ast->cmd, "cd\0", 3) == 0)
	{
		do_cd(data, ast);
	}
	else if (ft_strncmp(ast->cmd, "pwd\0", 4) == 0)
	{
		do_pwd(data, ast);
	}
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
		printf("Command not found :(\n");
}

void	ast(t_data *data)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		ft_error(data, "Failed ast malloc :(");
	ast->cmd = data->tokens[0];
	ast->home = getenv("HOME");
	check_cmd(data, ast);
}

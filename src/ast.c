/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/13 15:32:47 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_name(t_data *data)
{
	char	*ret;
	int		i;

	i = 0;
	while (data->tokens[1][i] != '=')
		i++;
	ret = malloc(sizeof(char) * i);
	i = 0;
	while (data->tokens[1][i] != '=')
	{
		ret[i] = data->tokens[1][i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*export_value(t_data *data)
{
	char	*ret;
	int		i;

	i = 0;
	while (data->tokens[1][i] != '=')
		i++;
	i++;
	int j = 0;
	while (data->tokens[1][i + j] != '\0')
		j++;
	ret = malloc(sizeof(char) * j);
	j = 0;
	while (data->tokens[1][i + j] != '\0')
	{
		ret[j] = data->tokens[1][i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	valid_export(t_data *data)
{
	int	i;
	int	aux;

	i = 1;
	while(data->tokens[1][i])
	{
		if (data->tokens[1][i] == '=' && i != 0)
			aux = 0;
		i++;
	}
	return (aux);
}

void	change_value(t_data *data)
{
	char	*name;
	t_list	*envo;

	name = export_name(data);
	envo = data->env;
	while (data->env)
	{
		if (ft_strcmp(data->env->name, name))
			break ;
		data->env = data->env->next;
	}
	free(data->env->value);
	data->env->value = export_value(data);
	data->env = envo;
	free(name);
}

int	export_exists(t_data *data)
{
	char	*name;
	int		aux;
	t_list	*envo;

	aux = 0;
	envo = data->env;
	name = export_name(data);
	while (data->env)
	{
		if (ft_strcmp(data->env->name, name))
			aux = 1;
		data->env = data->env->next;
	}
	data->env = envo;
	free(name);
	return (aux);
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
	else if (ft_strncmp(ast->cmd, "export\0", 7) == 0)
	{
		do_export(data, ast);
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/22 15:23:40 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_path_cmd(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("Fork: ");
	if (pid == 0)
	{
		if (access(data->tokens[0], 0) == 0)
			execve(data->tokens[0], data->tokens, data->envp);
		else
		{
			perror("Error");
			data->erno = errno;
			exit(data->erno);
		}
	}
	waitpid(pid, NULL, 0);
}

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
	else if (ft_strncmp(data->cmd, "unset\0", 6) == 0)
		do_unset(data);
	else if (ft_strncmp(data->cmd, "env\0", 4) == 0)
		do_env(data);
	else if (ft_strncmp(data->cmd, "exit\0", 5) == 0)
		do_exit(data);
	else if (ft_strncmp(data->cmd, "/", 1) == 0)
		do_path_cmd(data);
	else
		do_other(data);
}

void	ast(t_data *data)
{
	data->cmd = data->tokens[0];
	data->home = getenv("HOME");
	check_cmd(data);
}

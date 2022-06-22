/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/22 17:37:33 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_path_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("Fork: ");
	if (pid == 0)
	{
		if (access(cmd->cmd, 0) == 0)
			execve(cmd->cmd, cmd->tokens, data->envp);
		else
		{
			perror("Error");
			data->erno = errno;
			exit(data->erno);
		}
	}
	waitpid(pid, NULL, 0);
}

void	check_cmd(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		do_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
		do_cd(data);
	else if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		do_pwd(data);
	else if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
		do_export(data);
	else if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
		do_unset(data);
	else if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		do_env(data);
	else if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0)
		do_exit(data);
	else if (ft_strncmp(cmd->cmd, "/", 1) == 0)
		do_path_cmd(data, cmd);
	else
		do_other(data, cmd);
}

void	process_child_1(t_data *data, t_cmd *cmd, int *fd)
{
	(void) cmd;
	dup2(fd[1], 1);
	close(fd[0]);
	check_cmd(data, cmd);
}

void	process_child_2(t_data *data, t_cmd *cmd, int *fd)
{
	(void) cmd;
	dup2(fd[0], 0);
	close(fd[1]);
	check_cmd(data, cmd);
}

void	ast(t_data *data)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (data->cmd_lst->next != NULL)
	{
		if (pipe(fd) < 0)
		{
			perror("Pipe");
			data->erno = errno;
		}
		data->home = getenv("HOME");
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("Fork:");
			data->erno = errno;
		}
		if (pid1 == 0)
			process_child_1(data, data->cmd_lst, fd);
		pid2 = fork();
		if (pid2 < 0)
			perror("Fork: ");
		if (pid2 == 0)
			process_child_2(data, data->cmd_lst->next, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
	{
		check_cmd(data, data->cmd_lst);
	}
	// while (data->cmd_lst)
	// {
	// 	data->cmd_lst = data->cmd_lst->next;
	// }
	// data->cmd = data->tokens[0];;
}

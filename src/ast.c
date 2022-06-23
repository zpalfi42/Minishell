/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/23 17:17:19 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_path_cmd(t_data *data, t_cmd *cmd)
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

int	is_builtin(t_data *data, t_cmd *cmd)
{
	(void) data;
	if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0)
		return (1);
	return (0);
}

void	check_cmd(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		do_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
		do_cd(data, cmd);
	else if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		do_pwd(data, cmd);
	else if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
		do_export(data, cmd);
	else if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
		do_unset(data, cmd);
	else if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		do_env(data, cmd);
	else if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0)
		do_exit(data, cmd);
	else if (ft_strncmp(cmd->cmd, "/", 1) == 0)
		do_path_cmd(data, cmd);
	else
		do_other(data, cmd);
}

// void	process_child_1(t_data *data, t_cmd *cmd)
// {
// 	(void) cmd;
// 	dup2(data->fd[1], 1);
// 	close(data->fd[0]);
// 	check_cmd(data, cmd);
// 	exit(1);
// }

// void	process_child_2(t_data *data, t_cmd *cmd)
// {
// 	dup2(data->fd[0], 0);
// 	close(data->fd[1]);
// 	check_cmd(data, cmd);
// 	exit(1);
// }

void	exec(t_data *data, t_cmd *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->next != NULL)
	{
		dup2(data->fd[1], 1);
		close(data->fd[1]);
		close(data->fd[0]);
	}
	check_cmd(data, cmd);
}

void	ast(t_data *data)
{
	pid_t	pid;

	if (is_builtin(data, data->cmd_lst) && data->cmd_lst->next == NULL)
	{
		check_cmd(data, data->cmd_lst);
	}
	else
	{
		while (data->cmd_lst != NULL)
		{
			if (data->cmd_lst->next != NULL)
				pipe(data->fd);
			pid = fork();
			if (pid < 0)
				return ;
			if (pid == 0)
				exec(data, data->cmd_lst);
			if (data->cmd_lst->next != NULL)
			{
				dup2(data->fd[0], 0);
				close(data->fd[0]);
				close(data->fd[1]);
			}
			data->cmd_lst = data->cmd_lst->next;
		}
	}
	// if (data->cmd_lst->next != NULL)
	// {
	// 	if (pipe(data->fd) < 0)
	// 	{
	// 		perror("Pipe");
	// 		data->erno = errno;
	// 	}
	// 	data->home = getenv("HOME");
	// 	pid1 = fork();
	// 	if (pid1 < -1)
	// 	{
	// 		perror("Fork:");
	// 		data->erno = errno;
	// 	}
	// 	if (pid1 == 0)
	// 		process_child_1(data, data->cmd_lst);
	// 	pid2 = fork();
	// 	if (pid2 < 0)
	// 		perror("Fork: ");
	// 	if (pid2 == 0)
	// 		process_child_2(data, data->cmd_lst->next);
	// 	close(data->fd[0]);
	// 	close(data->fd[1]);
	// 	waitpid(pid1, NULL, 0);
	// 	waitpid(pid2, NULL, 0);
	// }
	// else
	// 	check_cmd(data, data->cmd_lst);
}

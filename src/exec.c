/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:47:01 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/14 14:57:50 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	exec_2(t_data *data, int in, int out)
{
	signal(SIGINT, handler_block);
	if (in == -1)
		exit(1);
	data->aux = is_builtin(data, data->cmd_lst);
	if (data->aux != 127)
	{
		redirect_io(in, out, 0);
		exec_builtin(data, data->cmd_lst, out, 1);
	}
	if (data->aux == 127)
	{
		redirect_io(in, out, 1);
		if (ft_strncmp(data->cmd_lst->cmd, "/", 1) == 0)
			do_path_cmd(data, data->cmd_lst);
		else
			do_other(data, data->cmd_lst);
	}
	return (data->aux);
}

void	exec(t_data *data, int in, int out)
{
	pid_t	pid;
	int		status;

	data->aux = 0;
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid < 0)
	{
		perror("Fork:");
		g_status = errno;
	}
	if (pid == 0)
		exec_2(data, in, out);
	else
		waitpid(pid, &status, 0);
	g_status = WEXITSTATUS(status);
}

void	exec_simple_2(t_data *data, int in, int out)
{
	if (in == -1)
		exit(1);
	redirect_io(in, out, 1);
	if (ft_strncmp(data->cmd_lst->cmd, "/", 1) == 0)
		do_path_cmd(data, data->cmd_lst);
	else
		do_other(data, data->cmd_lst);
}

void	exec_simple(t_data *data, int in, int out)
{
	pid_t			pid;
	int				status;

	status = 0;
	data->aux = is_builtin(data, data->cmd_lst);
	if (data->aux != 127)
		exec_builtin(data, data->cmd_lst, out, 0);
	else if (data->aux == 127)
	{
		g_status = 666;
		pid = fork();
		if (pid < 0)
		{
			perror("Fork:");
			g_status = errno;
		}
		if (pid == 0)
			exec_simple_2(data, in, out);
		else
			waitpid(pid, &status, 0);
		if (g_status != 130)
			g_status = WEXITSTATUS(status);
	}
}

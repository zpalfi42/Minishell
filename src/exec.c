/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:47:01 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/20 17:45:50 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_2(t_data *data, int in, int out)
{
	if (in == -1)
		exit(1);
	printf("out: %d\n", out);
	printf("in: %d\n", in);
	redirect_io(in, out);
	data->aux = is_builtin(data, data->cmd_lst);
	if (data->aux != 127)
	{
		printf("%d\n", out);
		exec_builtin(data, data->cmd_lst, out, 1);
		exit(1);
	}
	if (data->aux == 127)
	{
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
	int		aux;

	pid = fork();
	aux = 0;
	if (pid < 0)
	{
		perror("Fork:");
		data->erno = errno;
	}
	if (pid == 0)
		aux = exec_2(data, in, out);
	else
		waitpid(pid, NULL, 0);
}

void	exec_simple_2(t_data *data, int in, int out)
{
	if (in == -1)
		exit(1);
	redirect_io(in, out);
	if (ft_strncmp(data->cmd_lst->cmd, "/", 1) == 0)
		do_path_cmd(data, data->cmd_lst);
	else
		do_other(data, data->cmd_lst);
}

void	exec_simple(t_data *data, int in, int out)
{
	pid_t	pid;

	data->aux = is_builtin(data, data->cmd_lst);
	if (data->aux != 127)
		exec_builtin(data, data->cmd_lst, out, 0);
	else if (data->aux == 127)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork:");
			data->erno = errno;
		}
		if (pid == 0)
			exec_simple_2(data, in, out);
		else
			waitpid(pid, NULL, 0);
	}
}

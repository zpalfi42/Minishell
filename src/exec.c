/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:47:01 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:45:54 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
* exec_child() if the command is a builtin calls exec_builtin()
* after redirecting the input and the output with redirect_io().
* If the command is a path calls do_path_cmd(), else calls do_other()
* all after redirecting the input and the output with redirect_io().
*/

int	exec_child(t_data *data, int in, int out)
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

/*
* exec() creates a fork where it will call exec_child.
*/

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
		exec_child(data, in, out);
	else
		waitpid(pid, &status, 0);
	g_status = WEXITSTATUS(status);
}

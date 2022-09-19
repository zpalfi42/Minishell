/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:36:40 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:46:35 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
* exec_simple_no_builtin() first redirects the input and the output. 
* Then if it is a path, calls do_path_cmd, else calls do_other.
*/

void	exec_simple_no_builtin(t_data *data, int in, int out)
{
	if (in == -1)
		exit(1);
	redirect_io(in, out, 1);
	if (ft_strncmp(data->cmd_lst->cmd, "/", 1) == 0)
		do_path_cmd(data, data->cmd_lst);
	else
		do_other(data, data->cmd_lst);
}

/*
* exec_simple() if the command is a builtin it calls exec_builtin(),
* else it creates a fork and calls exec_simple_no_builtin().
*/

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
			exec_simple_no_builtin(data, in, out);
		else
			waitpid(pid, &status, 0);
		if (g_status != 130)
			g_status = WEXITSTATUS(status);
	}
}

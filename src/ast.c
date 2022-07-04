/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/04 14:45:06 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_data *data, t_cmd *cmd, int fd)
{
	(void) data;
	if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		return (do_echo(cmd, fd));
	else if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
		return (do_cd(data, cmd));
	else if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		return (do_pwd(data, cmd, fd));
	else if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
		return (do_export(data, cmd));
	else if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
		return (do_unset(data, cmd));
	else if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		return (do_env(data, cmd, fd));
	else if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0)
		return (do_exit(data, cmd));
	return (127);
}

void	redirect_io(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		if (in != 0)
			close(in);
		close(out);
	}
}

void	exec(t_data *data, int in, int out)
{
	int		aux;
	pid_t	pid;

	aux = is_builtin(data, data->cmd_lst, out);
	if (aux == 127)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork:");
			data->erno = errno;
		}
		if (pid == 0)
		{
			if (in == -1)
				exit(1);
			redirect_io(in, out);
			if (ft_strncmp(data->cmd_lst->cmd, "/", 1) == 0)
				do_path_cmd(data, data->cmd_lst);
			else
				do_other(data, data->cmd_lst);
		}
		else
			waitpid(pid, NULL, 0);
	}
}

void	assign_io(t_data *data, int *in, int *out, int fd[2])
{
	(void) in;
	if (data->cmd_lst->next)
	{
		if (pipe(fd) == -1)
		{
			perror("Pipe:");
			data->erno = errno;
		}
		*out = fd[1];
	}
	else
		*out = 1;
}

void	ast(t_data *data)
{
	int		fd[2];
	int		in;
	int		out;
	int		first;

	first = 1;
	while (data->cmd_lst != NULL)
	{
		if (first)
			in = 0;
		else
			in = fd[0];
		assign_io(data, &in, &out, fd);
		if (data->cmd_lst->cmd != NULL)
			exec(data, in, out);
		if (out != 1)
			close(out);
		if (in != 0)
			close(in);
		data->cmd_lst = data->cmd_lst->next;
		first = 0;
	}
}

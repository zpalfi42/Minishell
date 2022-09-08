/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/08 13:28:23 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_data *data, t_cmd *cmd, int fd, int mode)
{
	if (data->aux == 1)
		do_echo(data, cmd, fd, mode);
	else if (data->aux == 2)
		(do_cd(data, cmd, mode));
	else if (data->aux == 3)
		do_pwd(data, cmd, fd, mode);
	else if (data->aux == 4)
		do_export(data, cmd, mode, fd);
	else if (data->aux == 5)
		do_unset(data, cmd, mode);
	else if (data->aux == 6)
		do_env(data, cmd, fd, mode);
	else if (data->aux == 7)
		do_exit(data, cmd, mode);
}

int	is_builtin(t_data *data, t_cmd *cmd)
{
	(void) data;
	if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
		return (2);
	else if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		return (3);
	else if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
		return (4);
	else if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
		return (5);
	else if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		return (6);
	else if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0)
		return (7);
	return (127);
}

void	redirect_io(int in, int out, int mode)
{
	if (in != 0)
	{
		close(0);
		dup2(in, 0);
		close(in);
	}
	if (out != 1 && mode)
	{
		close(1);
		dup2(out, 1);
		if (in != 0)
			close(in);
		close(out);
	}
}

void	ast_simple(t_data *data, int first)
{
	int		fd[2];
	int		in;
	int		out;

	if (first == 1 && data->cmd_lst->next == NULL)
	{
		if (first)
			in = 0;
		else
			in = fd[0];
		assign_io(data, &in, &out, fd);
		if (data->cmd_lst->cmd != NULL)
			exec_simple(data, in, out);
		if (out != 1)
			close(out);
		if (in != 0)
			close(in);
		data->cmd_lst = data->cmd_lst->next;
		first = 0;
	}
}

void	ast(t_data *data)
{
	int		fd[2];
	int		in;
	int		out;
	int		first;

	first = 1;
	data->home = getenv("HOME");
	ast_simple(data, first);
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

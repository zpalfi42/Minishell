/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:55 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:48:17 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* exec_builtin() executes one of our builtins.
*/

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
	else if (data->aux == 8)
		do_dir(data, cmd, mode);
}

/*
* is_builitn() checks if the comand provided is some of our builtins or not.
*/

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
	else if (ft_strncmp(cmd->cmd, "/\0", 2) == 0)
		return (8);
	return (127);
}

/*
* redirect_io() move the stdin and stdout to the in and the out provided.
*/

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

/*
* ast_simple() only executes something if only one cmd is sent. First
* assigns the input and output with assign_io(). then
* calls exec_simple() to execute the command, and finally it closes
* out and returns 1.
*/

int	ast_simple(t_data *data, int first)
{
	int		fd[2];
	int		in;
	int		out;
	t_cmd	*n;

	if (first == 1 && data->cmd_lst->next == NULL)
	{
		n = data->cmd_lst;
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
		data->cmd_lst = n;
		first = 0;
		return (1);
	}
	return (0);
}

/*
* ast() is the main executor. If there is only one command
* it calls ast_simple(). Else while there are no more commands
* it first assign the with assign_io(). then
* calls exec() to execute the command, and finally it closes in
* and out and goes to the next cmd.
*/

void	ast(t_data *data)
{
	int		fd[2];
	int		in;
	int		out;
	int		first;
	t_cmd	*n;

	first = 1;
	data->ast = ast_simple(data, first);
	n = data->cmd_lst;
	while (data->cmd_lst != NULL && data->ast == 0)
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

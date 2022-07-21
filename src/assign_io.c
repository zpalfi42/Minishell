/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:48:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/21 15:29:24 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redirect(t_files *files)
{
	int	fd;

	fd = 1;
	while (files != NULL)
	{
		if (files->type == 0)
			fd = open(files->filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (files->type == 1)
			fd = open(files->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
		if (fd == -1)
			perror(files->filename);
		if (files->next != NULL)
			close(fd);
		files = files->next;
	}
	return (fd);
}

int	in_redirect(t_files *files)
{
	int	fd;

	fd = 0;
	while (files != NULL)
	{
		if (files->filename != NULL)
			fd = open(files->filename, O_RDONLY, 0777);
		else
			fd = files->end[0];
		if (fd == -1)
		{
			perror(files->filename);
		}
		if (files->next != NULL)
			close(fd);
		files = files->next;
	}
	return (fd);
}

void	assign_io(t_data *data, int *in, int *out, int fd[2])
{
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
	if (data->cmd_lst->infiles != NULL)
		*in = in_redirect(data->cmd_lst->infiles);
	if (data->cmd_lst->outfiles != NULL)
		*out = out_redirect(data->cmd_lst->outfiles);
}

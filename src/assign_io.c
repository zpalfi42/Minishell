/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:48:17 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 12:29:15 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redirect(t_files *files)
{
	int		fd;
	t_files	*aux;

	fd = 1;
	while (files != NULL)
	{
		aux = files->next;
		if (files->type == 0 && files->filename != NULL)
			fd = open(files->filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (files->type == 1 && files->filename != NULL)
			fd = open(files->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
		if (fd == -1)
		{
			perror(files->filename);
			break ;
		}
		if (files->next != NULL)
			close(fd);
		if (files->filename != NULL)
			free(files->filename);
		free(files);
		files = aux;
	}
	return (fd);
}

int	in_redirect(t_files *files)
{
	int		fd;
	t_files	*aux;

	fd = 0;
	while (files != NULL)
	{
		aux = files->next;
		if (files->filename != NULL && files->filename[0] != '\0')
			fd = open(files->filename, O_RDONLY, 0777);
		else
			fd = files->end[0];
		if (fd == -1)
		{
			perror(files->filename);
			break ;
		}
		if (files->next != NULL)
			close(fd);
		if (files->filename != NULL)
			free(files->filename);
		free(files);
		files = aux;
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
	if (data->cmd_lst->outfiles != NULL && *in != -1)
		*out = out_redirect(data->cmd_lst->outfiles);
}

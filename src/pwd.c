/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:25:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/12 13:57:34 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(t_data *data, t_cmd *cmd, int fd, int mode)
{
	char	*pwd;

	(void) cmd;
	pwd = malloc(sizeof(char) * 4097);
	if (!pwd)
		ft_error(data, "Failed malloc :(");
	if (getcwd(pwd, 4096) == NULL)
	{
		perror("getcwd");
		data->erno = errno;
		if (mode == 1)
			exit(data->erno);
	}
	else
		data->erno = 0;
	ft_putendl_fd(pwd, fd);
	free(pwd);
	if (mode == 1)
		exit (0);
	return (1);
}

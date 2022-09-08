/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:25:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/08 13:28:40 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(t_data *data, t_cmd *cmd, int fd, int mode)
{
	char	*pwd;

	(void) data;
	if (cmd->tokens[1] != 0)
	{
		printf("Pwd: Too many arguments\n");
		data->erno = 1;
	}
	else
	{
		pwd = malloc(sizeof(char) * 200);
		if (!pwd)
			ft_error(data, "Failed malloc :(");
		if (getcwd(pwd, 199) == NULL)
		{
			perror("getcwd");
			data->erno = errno;
		}
		ft_putendl_fd(pwd, fd);
		free(pwd);
		data->erno = 0;
	}
	if (mode == 1)
		exit (1);
	return (1);
}

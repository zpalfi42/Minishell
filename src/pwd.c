/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:25:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/14 13:20:26 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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
		g_status = errno;
		if (mode == 1)
			exit(g_status);
	}
	else
		g_status = 0;
	ft_putendl_fd(pwd, fd);
	free(pwd);
	if (mode == 1)
		exit (0);
	return (1);
}

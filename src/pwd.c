/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:25:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/23 15:31:30 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(t_data *data, t_cmd *cmd)
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
		printf("%s\n", pwd);
		free(pwd);
		data->erno = 0;
	}
}

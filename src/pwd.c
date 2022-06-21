/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:25:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/21 16:04:42 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(t_data *data)
{
	char	*pwd;

	(void) data;
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
}

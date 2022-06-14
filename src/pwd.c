/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:25:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 14:22:22 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(t_data *data)
{
	char	*pwd;

	(void) data;
	pwd = malloc(sizeof(char) * 200);
	if (getcwd(pwd, 199) == NULL)
		perror("getcwd");
	printf("%s\n", pwd);
}

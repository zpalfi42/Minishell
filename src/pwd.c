/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:25:32 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/13 14:25:57 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pwd(t_data *data, t_ast *ast)
{
	char	*pwd;

	(void) data;
	(void) ast;

	pwd = malloc(sizeof(char) * 200);
	if (getcwd(pwd, 199) == NULL)
	{
		perror("getcwd");
	}
	printf("%s\n", pwd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:05:48 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/04 14:45:26 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_files	*last_files(t_files	*files)
{
	if (!files)
		return (NULL);
	while (files->next)
		files = files->next;
	return (files);
}

void	files_add_back(t_files **files, t_files *new)
{
	t_files	*t;

	if (!files || !new)
		return ;
	t = *files;
	if (*files)
	{
		t = last_files(*files);
		t->next = new;
	}
	else
		*files = new;
}

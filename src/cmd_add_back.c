/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:04:33 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/12 16:41:37 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*last_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	cmd_add_back(t_cmd	**lst, t_cmd *new)
{
	t_cmd	*t;

	if (!lst || !new)
		return (-1);
	t = *lst;
	if (*lst)
	{
		t = last_cmd(*lst);
		t->next = new;
	}
	else
		*lst = new;
	return (0);
}

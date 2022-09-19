/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_after_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:02:59 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:53:39 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* control_redir_alone() helps return_cmd_after_redir() to know
* if the redirections spotted are with the filenames or are alone. 
* This is helpfull to know if we have to skip 1 or 2 tokens.
*/

static int	control_redir_alone(char **tokens, int i, int aux)
{
	if (tokens[i][0] == '<')
	{
		if (tokens[i][1] == '\0')
			aux = 1;
		else
			aux = 0;
	}
	else if (tokens[i][0] == '>')
	{
		if (tokens[i][1] == '\0')
			aux = 1;
		else if (tokens[i][1] == '>')
		{
			if (tokens[i][2] == '\0')
				aux = 1;
			else
				aux = 0;
		}
		else
			aux = 0;
	}
	return (aux);
}

/*
* return_cmd_after_redir() returns the comand string found
* after the redirections.
*/

static char	*return_cmd_after_redir(t_cmd *n, char **tokens, int i, int j)
{
	int	aux;

	aux = 0;
	while (i < j)
	{
		if (tokens[i][0] != '<' && tokens[i][0] != '>')
		{
			if (aux == 1)
				aux = 0;
			else
			{
				n->aux = i;
				return (tokens[i]);
			}
		}
		aux = control_redir_alone(tokens, i, aux);
		i++;
	}
	n->aux = i;
	return (NULL);
}

/*
* cmd_control_redirections() tries to find where the command is located
* if there are some redirections at the begining of the line.
*/

void	find_cmd_after_redir(char **tokens, t_cmd *n, int i, int j)
{
	if (tokens[i][0] == '<' || tokens[i][0] == '>')
		n->cmd = return_cmd_after_redir(n, tokens, i, j);
	else
	{
		n->aux = i;
		n->cmd = tokens[i];
	}
}

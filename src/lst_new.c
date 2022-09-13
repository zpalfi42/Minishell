/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:31 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/13 15:20:25 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_out_parser(t_cmd *n, t_data *data, int z, int j)
{
	n->first_1 = 1;
	n->first_2 = 1;
	while (data->tokens[++z] != 0 && z < j)
	{
		if (data->tokens[z][0] == '>' && data->tokens_type[z] == 0)
			z = output_file(n, data->tokens, z, data);
		else if (data->tokens[z][0] == '<' && data->tokens_type[z] == 0)
			z = input_file(n, data->tokens, z, data);
		if (z == -1)
			return (0);
	}
	if (n->first_1 == 1)
		n->outfiles = NULL;
	if (n->first_2 == 1)
		n->infiles = NULL;
	return (1);
}

int	find_cmd_2(char **tokens, int i, int aux)
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

char	*find_cmd(t_cmd *n, char **tokens, int i, int j)
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
		aux = find_cmd_2(tokens, i, aux);
		i++;
	}
	n->aux = i;
	return (NULL);
}

void	cmd_control_redirections(char **tokens, t_cmd *n, int i, int j)
{
	if (tokens[i][0] == '<' || tokens[i][0] == '>')
		n->cmd = find_cmd(n, tokens, i, j);
	else
	{
		n->aux = i;
		n->cmd = tokens[i];
	}
}

t_cmd	*cmd_lst_new(t_data *data, char **tokens, int i, int j)
{
	t_cmd	*n;
	int		z;

	n = (t_cmd *)malloc(sizeof(t_cmd));
	if (!n)
		return (NULL);
	cmd_control_redirections(tokens, n, i, j);
	n->arg = malloc(sizeof(char *) * (j - i));
	data->z = i - 1;
	while (tokens[++data->z] != 0 && data->z < j)
		if ((tokens[data->z][0] == '<' || tokens[data->z][0] == '>')
			&& data->tokens_type[data->z] == 0)
			break ;
	n->tokens = malloc(sizeof(char *) * (data->z - i + 1));
	n->tokens_type = malloc(sizeof(int) * (data->z - i + 1));
	z = in_out_parser(n, data, i - 1, j);
	if (z == 0)
		return (NULL);
	cmd_tokens_saver(n, data, n->aux, j);
	n->next = NULL;
	return (n);
}

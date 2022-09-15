/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:31 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 13:04:49 by zpalfi           ###   ########.fr       */
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

int	redir_type(char **tokens, int i)
{
	if (tokens[i][1] == '\0')
		return (2);
	else if (tokens[i][1] == '<' || tokens[i][1] == '>')
	{
		if (tokens[i][2] == '\0')
			return (2);
		return (1);
	}
	else
		return (1);
}

void	count_tokens_cmd(t_data *data, char **tokens, int j)
{
	int	aux;

	aux = 0;
	while (tokens[data->z + aux] != 0 && data->z < j)
	{
		if ((tokens[data->z + aux][0] == '<' || tokens[data->z + aux][0] == '>')
			&& data->tokens_type[data->z + aux] == 0)
			aux += redir_type(tokens, data->z + aux);
		else
			data->z++;
	}	
}

t_cmd	*cmd_lst_new(t_data *data, char **tokens, int i, int j)
{
	t_cmd	*n;
	int		z;

	n = (t_cmd *)malloc(sizeof(t_cmd));
	if (!n)
		return (NULL);
	find_cmd_after_redir(tokens, n, i, j);
	n->arg = malloc(sizeof(char *) * (j - i));
	data->z = i;
	count_tokens_cmd(data, tokens, j);
	n->tokens = malloc(sizeof(char *) * (data->z - i + 1));
	n->tokens_type = malloc(sizeof(int) * (data->z - i + 1));
	z = in_out_parser(n, data, i - 1, j);
	if (z == 0)
		return (NULL);
	cmd_tokens_saver(n, data, n->aux, j);
	n->next = NULL;
	return (n);
}

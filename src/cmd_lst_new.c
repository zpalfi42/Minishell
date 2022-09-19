/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:31 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 13:28:52 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in_out_parser() parse all the redirections we have in our data->tokens
// and saves the information of the redirection in a files structure.
// If it is a output redirection it saves it in *outfiles, if it is a input
// redirection it save it in *infiles.

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

// Helps cmd_tokens_saver && _counter to know if they have to skip 1 or 2 tokens
// 1 if the filename is in the same token as the redirection,
// 2 if the filename and the redirection are in different tokens.

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

// cmd_tokens_saver() save all the non-redirection tokens (included the command)
// and their token_type. It also save the arguments (tokens without the command)

void	cmd_tokens_saver(t_cmd *n, t_data *data, int i, int j)
{
	int	z;

	z = 0;
	n->tokens[z] = data->tokens[i];
	n->tokens_type[z] = data->tokens_type[i];
	i++;
	while (data->tokens[i] != 0 && i < j)
	{
		if ((data->tokens[i][0] == '<' || data->tokens[i][0] == '>')
			&& data->tokens_type[i] == 0)
			i += redir_type(data->tokens, i);
		else
		{
			n->arg[z] = data->tokens[i];
			n->tokens[z + 1] = data->tokens[i];
			n->tokens_type[z + 1] = data->tokens_type[i];
			z++;
			i++;
		}
	}
	n->arg[z] = 0;
	n->tokens[z + 1] = 0;
	n->tokens_type[z + 1] = -1;
}

// cmd_tokens_counter() count the non-redirection tokens.

void	cmd_tokens_counter(t_data *data, char **tokens, int j)
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

// cmd_lst_new() creates a new cmd structure to add in the cmd list. In this
// structure we save the tokens, tokens_type, the arguments after the command
// and all the redirections in 2 files structures (infiles && outfiles).

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
	cmd_tokens_counter(data, tokens, j);
	n->tokens = malloc(sizeof(char *) * (data->z - i + 1));
	n->tokens_type = malloc(sizeof(int) * (data->z - i + 1));
	z = in_out_parser(n, data, i - 1, j);
	if (z == 0)
		return (NULL);
	cmd_tokens_saver(n, data, n->aux, j);
	n->next = NULL;
	return (n);
}

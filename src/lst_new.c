/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:31 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/04 16:35:18 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*files_lst_new(char *name, int mode, char c)
{
	t_files	*n;
	int		i;
	int		j;

	i = 0;
	j = 2;
	if (mode == 2)
		j = 1;
	n = (t_files *)malloc(sizeof(t_files));
	if (!n)
		return (NULL);
	n->type = mode;
	while (name[i] == c && i < j)
		i++;
	j = 0;
	while (name[j + i] != '\0')
		j++;
	n->filename = malloc(sizeof(char) * (j + 1));
	j = -1;
	while (name[++j + i] != '\0')
		n->filename[j] = name[j + i];
	n->next = NULL;
	return (n);
}

void	cmd_tokens_saver(t_cmd *n, t_data *data, int i, int j)
{
	int	z;

	z = 0;
	n->tokens[z] = data->tokens[i];
	n->tokens_type[z] = data->tokens_type[i];
	while (data->tokens[++i] != 0 && i < j)
	{
		if (data->tokens[i][0] == '<' || data->tokens[i][0] == '>')
			break ;
		n->arg[z] = data->tokens[i];
		n->tokens[z + 1] = data->tokens[i];
		n->tokens_type[z + 1] = data->tokens_type[i];
		z++;
	}
	n->arg[z] = 0;
	n->tokens[z + 1] = 0;
	n->tokens_type[z + 1] = -1;
}

void	in_out_parser(t_cmd *n, char **tokens, int z, int j)
{
	n->first_1 = 1;
	n->first_2 = 1;
	while (tokens[++z] != 0 && z < j)
	{
		if (tokens[z][0] == '>')
			z = output_file(n, tokens, z);
		else if (tokens[z][0] == '<')
			z = input_file(n, tokens, z);
	}
	if (n->first_1 == 1)
		n->outfiles = NULL;
	if (n->first_2 == 1)
		n->infiles = NULL;
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
		i++;
	}
	n->aux = i;
	return (NULL);
}

t_cmd	*cmd_lst_new(t_data *data, char **tokens, int i, int j)
{
	t_cmd	*n;
	int		z;

	n = (t_cmd *)malloc(sizeof(t_cmd));
	if (!n)
		return (NULL);
	if (tokens[i][0] == '<' || tokens[i][0] == '>')
		n->cmd = find_cmd(n, tokens, i, j);
	else
	{
		n->aux = i;
		n->cmd = tokens[i];
	}
	n->arg = malloc(sizeof(char *) * (j - i));
	z = i - 1;
	while (tokens[++z] != 0 && z < j)
		if (tokens[z][0] == '<' || tokens[z][0] == '>')
			break ;
	n->tokens = malloc(sizeof(char *) * (z - i + 1));
	n->tokens_type = malloc(sizeof(int) * (z - i + 1));
	in_out_parser(n, tokens, i - 1, j);
	cmd_tokens_saver(n, data, n->aux, j);
	n->next = NULL;
	return (n);
}

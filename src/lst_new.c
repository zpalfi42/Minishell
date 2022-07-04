/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:31 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/04 14:40:02 by zpalfi           ###   ########.fr       */
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

void	cmd_tokens_saver(t_cmd *n, char **tokens, int i, int j)
{
	int	z;

	z = 0;
	n->tokens[z] = tokens[i];
	while (tokens[++i] != 0 && i < j)
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			break ;
		n->arg[z] = tokens[i];
		n->tokens[z + 1] = tokens[i];
		z++;
	}
	n->arg[z] = 0;
	n->tokens[z + 1] = 0;
}

void	in_out_parser(t_cmd *n, char **tokens, int z, int j)
{
	n->first = 1;
	while (tokens[++z] != 0 && z < j)
	{
		if (tokens[z][0] == '>')
			z = output_file(n, tokens, z);
		else if (tokens[z][0] == '<')
			z = input_file(n, tokens, z);
	}
	if (n->first == 1)
		n->files = NULL;
}

t_cmd	*cmd_lst_new(char **tokens, int i, int j)
{
	t_cmd	*n;
	int		z;

	n = (t_cmd *)malloc(sizeof(t_cmd));
	if (!n)
		return (NULL);
	n->cmd = tokens[i];
	n->arg = malloc(sizeof(char *) * (j - i));
	z = i;
	while (tokens[z] != 0 && z < j)
	{
		if (tokens[z][0] == '<' || tokens[z][0] == '>')
			break ;
		z++;
	}
	n->tokens = malloc(sizeof(char *) * (z - i + 1));
	in_out_parser(n, tokens, i - 1, j);
	cmd_tokens_saver(n, tokens, i, j);
	n->next = NULL;
	return (n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:11:58 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/11 16:45:42 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_output_file(t_cmd *n, char **tokens, int z)
{
	if (tokens[z][2] == '\0')
	{
		if (n->first_1 == 1)
		{
			n->outfiles = files_lst_new(tokens[++z], 1, '>');
			n->first_1 = 0;
		}
		else
			files_add_back(&n->outfiles,
				files_lst_new(tokens[++z], 1, '>'));
	}
	else
	{
		if (n->first_1 == 1)
		{
			n->outfiles = files_lst_new(tokens[z], 1, '>');
			n->first_1 = 0;
		}
		else
			files_add_back(&n->outfiles, files_lst_new(tokens[z], 1, '>'));
	}
	return (z);
}

int	output_file(t_cmd *n, char **tokens, int z)
{
	if (tokens[z][1] == '\0')
	{
		if (n->first_1 == 1)
		{
			n->outfiles = files_lst_new(tokens[++z], 0, '>');
			n->first_1 = 0;
		}
		else
			files_add_back(&n->outfiles, files_lst_new(tokens[++z], 0, '>'));
	}
	else if (tokens[z][1] == '>')
		z = double_output_file(n, tokens, z);
	else
	{
		if (n->first_1 == 1)
		{
			n->outfiles = files_lst_new(tokens[z], 0, '>');
			n->first_1 = 0;
		}
		else
			files_add_back(&n->outfiles, files_lst_new(tokens[z], 0, '>'));
	}
	return (z);
}

int	input_file(t_cmd *n, char **tokens, int z)
{
	if (tokens[z][1] == '\0')
	{
		if (n->first_2 == 1)
		{
			n->infiles = files_lst_new(tokens[++z], 2, '<');
			n->first_2 = 0;
		}
		else
			files_add_back(&n->infiles, files_lst_new(tokens[++z], 2, '<'));
	}
	else
	{
		if (n->first_2 == 1)
		{
			n->infiles = files_lst_new(tokens[z], 2, '<');
			n->first_2 = 0;
		}
		else
			files_add_back(&n->infiles, files_lst_new(tokens[z], 2, '<'));
	}
	return (z);
}

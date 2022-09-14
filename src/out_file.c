/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:54:43 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/14 13:01:53 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_simple_out(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[++z] != NULL && n->first_1 == 1)
	{
		n->outfiles = files_lst_new(tokens[z], 1, '>',
				data->tokens_type[z]);
		if (n->outfiles == NULL)
			return (-1);
		n->first_1 = 0;
	}
	else if (tokens[z] != NULL)
	{
		if (files_add_back(&n->outfiles,
				files_lst_new(tokens[z], 1, '>',
					data->tokens_type[z])) == -1)
			return (-1);
	}
	else
	{
		printf("parse error near '%s'\n", tokens[z -1]);
		return (-1);
	}
	return (z);
}

static int	double_output_file(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[z][2] == '\0')
		z = double_simple_out(n, tokens, z, data);
	else
	{
		if (n->first_1 == 1)
		{
			n->outfiles = files_lst_new(tokens[z] + 2, 1, '>',
					data->tokens_type[z]);
			if (n->outfiles == NULL)
				return (-1);
			n->first_1 = 0;
		}
		else
			if (files_add_back(&n->outfiles,
					files_lst_new(tokens[z] + 2, 1, '>',
						data->tokens_type[z])) == -1)
				return (-1);
	}
	return (z);
}

static int	output_simple_file(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[++z] != NULL && n->first_1 == 1)
	{
		n->outfiles = files_lst_new(tokens[z], 0, '>',
				data->tokens_type[z]);
		if (n->outfiles == NULL)
			return (-1);
		n->first_1 = 0;
	}
	else if (tokens[z] != NULL)
	{
		if (files_add_back(&n->outfiles, files_lst_new(tokens[z], 0, '>',
					data->tokens_type[z])) == -1)
			return (-1);
	}
	else
	{
		printf("parse error near '%s'\n", tokens[z -1]);
		return (-1);
	}
	return (z);
}

int	output_file(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[z][1] == '\0')
		z = output_simple_file(n, tokens, z, data);
	else if (tokens[z][1] == '>')
		z = double_output_file(n, tokens, z, data);
	else
	{
		if (n->first_1 == 1)
		{
			n->outfiles = files_lst_new(tokens[z] + 1,
					0, '>', data->tokens_type[z]);
			if (n->outfiles == NULL)
				return (-1);
			n->first_1 = 0;
		}
		else
			if (files_add_back(&n->outfiles, files_lst_new(tokens[z] + 1
						, 0, '>', data->tokens_type[z])) == -1)
				return (-1);
	}
	return (z);
}

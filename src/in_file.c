/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:11:58 by zpalfi            #+#    #+#             */
/*   Updated: 2022/07/20 17:03:59 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_simple_in(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (n->first_2 == 1 && tokens[++z] != NULL)
	{
		n->infiles = files_lst_new(tokens[z], 3, '<', data->tokens_type[z]);
		if (n->infiles == NULL)
			return (-1);
		n->first_2 = 0;
	}
	else if (tokens[z] != NULL)
	{
		if (files_add_back(&n->infiles,
				files_lst_new(tokens[z], 3, '<',
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

static int	double_input_file(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[z][2] == '\0')
		z = double_simple_in(n, tokens, z, data);
	else
	{
		if (n->first_1 == 1)
		{
			n->infiles = files_lst_new(tokens[z], 3, '<', data->tokens_type[z]);
			if (n->infiles == NULL)
				return (-1);
			n->first_1 = 0;
		}
		else
			if (files_add_back(&n->infiles, files_lst_new(tokens[z], 3, '>',
						data->tokens_type[z])) == -1)
				return (-1);
	}
	return (z);
}

static int	simple_input_file(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (n->first_2 == 1 && tokens[++z] != NULL)
	{
		n->infiles = files_lst_new(tokens[z], 2, '<', data->tokens_type[z]);
		if (n->infiles == NULL)
			return (-1);
		n->first_2 = 0;
	}
	else if (tokens[z] != NULL)
	{
		if (files_add_back(&n->infiles, files_lst_new(tokens[z]
					, 2, '<', data->tokens_type[z])) == -1)
			return (-1);
	}
	else
	{
		printf("parse error near '%s'\n", tokens[z -1]);
		return (-1);
	}
	return (z);
}

int	input_file(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[z][1] == '\0')
		z = simple_input_file(n, tokens, z, data);
	else if (tokens[z][1] == '<')
		z = double_input_file(n, tokens, z, data);
	else
	{
		if (n->first_2 == 1 && data->tokens[z][1] != '>')
		{
			n->infiles = files_lst_new(tokens[z], 2, '<', data->tokens_type[z]);
			if (n->infiles == NULL)
				return (-1);
			n->first_2 = 0;
		}
		else
			if (files_add_back(&n->infiles, files_lst_new(tokens[z]
						, 2, '<', data->tokens_type[z])) == -1)
				return (-1);
	}
	return (z);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:11:58 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 13:45:46 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// it does the same as input_simple_file but with another args.

static int	double_simple_in(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[++z] != NULL && n->first_2 == 1)
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

// double_input_file() first sees if ">>"" and filename are in the same token,
// if thei are not in the same token it calls double_simple_in().
// else it does the same as input_simple_file() but with another args.

static int	double_input_file(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[z][2] == '\0')
		z = double_simple_in(n, tokens, z, data);
	else
	{
		if (n->first_1 == 1)
		{
			n->infiles = files_lst_new(tokens[z] + 2, 3,
					'<', data->tokens_type[z]);
			if (n->infiles == NULL)
				return (-1);
			n->first_1 = 0;
		}
		else
			if (files_add_back(&n->infiles, files_lst_new(tokens[z] + 2, 3, '>',
						data->tokens_type[z])) == -1)
				return (-1);
	}
	return (z);
}

// input_simple_file() if it is the first input redirection of the cmd struct
// it creates the structure and saves all the info with files_lst_new(). If
// it is not he first one it adds it back with files_add_back().

static int	simple_input_file(t_cmd *n, char **tokens, int z, t_data *data)
{
	if (tokens[++z] != NULL && n->first_2 == 1)
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

// input_file() saves || creates a t_files struct and saves all the information
// of the redirection sent. 
// If the redirection is alone it calls input_simple_file().
// If it is a double input redirection it calls double_input_file().
// And if the redirection is with the filename it does de else{}

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
			n->infiles = files_lst_new(tokens[z] + 1, 2,
					'<', data->tokens_type[z]);
			if (n->infiles == NULL)
				return (-1);
			n->first_2 = 0;
		}
		else
			if (files_add_back(&n->infiles, files_lst_new(tokens[z] + 1
						, 2, '<', data->tokens_type[z])) == -1)
				return (-1);
	}
	return (z);
}

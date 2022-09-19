/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:54:43 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 16:55:03 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* it does the same as output_simple_file but with another args.
*/

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

/*
* double_output_file() first sees if ">>"" and filename are in the same token,
* if thei are not in the same token it calls double_simple_out().
* else it does the same as output_simple_file() but with another args.
*/

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

/*
* output_simple_file() if it is the first outut redirection of the cmd struct
* it creates the structure and saves all the info with files_lst_new(). If
* it is not he first one it adds it back with files_add_back().
*/

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

/*
* output_file() saves || creates a t_files struct and saves all the information
* of the redirection sent. 
* If the redirection is alone it calls output_simple_file().
* If it is a double output redirection it calls double_output_file().
* And if the redirection is with the filename it does de else{}
*/

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

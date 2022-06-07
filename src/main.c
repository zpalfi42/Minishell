/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/07 17:06:12 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		if (data->tokens[i])
			free(data->tokens[i]);
		i++;
	}
	if (data->tokens[i])
		free(data->tokens[i]);
	free(data->tokens);
}

void	countq(t_data *data)
{
	int	i;

	i = 0;
	data->dc = 0;
	data->sc = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == 34)
			data->dc++;
		else if (data->line[i] == 39)
			data->sc++;
		i++;
	}
	data->dc_2 = data->dc;
	data->sc_2 = data->sc;
}

void	parser(t_data *data)
{
	data->i = 0;
	countq(data);
	count_tokens(data);
	save_tokens(data);
	free_all(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	argc = 0;
	argv = NULL;
	envp = NULL;
	print_miniconcha();
	data = (t_data *)malloc(sizeof(t_data));
	if (sig_handler())
		return (1);
	while (42)
	{
		data->count = 0;
		data->word = 0;
		data->line = readline("\033[1;32mminiconcha>$ \033[1;00m");
		if (data->line == 0)
		{
			free(data->line);
			free(data);
			exit (1);
		}
		if (*data->line != '\0')
			parser(data);
		free(data->line);
	}
}

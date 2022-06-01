/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/01 16:54:10 by zpalfi           ###   ########.fr       */
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

void	parser(t_data *data)
{
	int i;

	i = 0;
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
	count_words(data);
	data->tokens = (char **)malloc(sizeof(char *) * (data->count + 1));
	if (!data->tokens)
	{
		printf("MALLOC ERROR\n");
		exit(1);
	}
	data->tokens[data->count] = 0;
	save_tokens(data);
	i = 0;
	while (data->tokens[i])
	{
		printf("%s\n", data->tokens[i]);
		i++;
	}
	free_all(data);
}

int main(int argc, char **argv, char **envp)
{
	t_data  *data;

	argc = 0;
	argv = NULL;
	envp = NULL;
	print_miniconcha();
    data = (t_data *)malloc(sizeof(t_data));
	if (sig_handler())
		return (1);
	while (42)
	{
		data->dc = 0;
		data->sc = 0;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/02 18:33:16 by ealonso-         ###   ########.fr       */
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
	while (data->line[i] != '\0')
	{
		if (data->line[i] == 34)
			data->dc++;
		else if (data->line[i] == 39)
			data->sc++;
		i++;
	}
}

void	save_tokens(t_data *data)
{
	int	i;
	int	j;
	int k;

	k = 0;
	j = 0;
	i = 0;
	data->tokens = (char **)malloc(sizeof(char *) * (data->count + 1));
	if (!data->tokens)
		exit (0);
	data->tokens[data->count] = 0;
	while (data->line[i] != '\0')
	{
		while (data->line[i] != ' ' && data->line[i] != '\0')
		{
			if (data->line[i] == 34 && data->dc > 1)
			{
				i++;
				data->dc_2--;
				while (data->line[i] != 34 && data->line[i] != '\0')
					i++;
					j++;
				if (data->line[i] == 34)
				{
					data->dc_2--;
					i++;
					j++;
				}
			}
			else if (data->line[i] == 39 && data->sc > 1)
			{
				i++;
				data->sc_2--;
				while (data->line[i] != 39 && data->line[i] != '\0')
					i++;
				if (data->line[i] == 39)
				{
					data->sc_2--;
					i++;
				}
			}
			else
			{
				i++;
				j++;
			}
		}
		data->tokens[data->word] = malloc(sizeof(char) * j);
		data->tokens[data->word][j] = '\0';
		while (j != 0)
		{
			data->tokens[data->word][k++] = data->line[i - j];
			j--;
		}
		// printf("hi %s", data->tokens[1]);
		data->word++;
		k = 0;
		j = 0;
		if (data->line[i] == ' ')
			i++;
	}
}

void	count_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i] != '\0')
	{
		while (data->line[i] != ' ' && data->line[i] != '\0')
		{
			if (data->line[i] == 34 && data->dc > 1)
			{
				i++;
				data->dc--;
				while (data->line[i] != 34 && data->line[i] != '\0')
					i++;
				if (data->line[i] == 34)
				{
					data->dc--;
					i++;
				}
			}
			else if (data->line[i] == 39 && data->sc > 1)
			{
				i++;
				data->sc--;
				while (data->line[i] != 39 && data->line[i] != '\0')
					i++;
				if (data->line[i] == 39)
				{
					data->sc--;
					i++;
				}
			}
			else
				i++;
		}
		if (data->line[i] == ' ')
			i++;
		// printf("%c\n", data->line[i]);
		data->count++;
	}
}

void	parser(t_data *data)
{
	int	i;

	countq(data);
	data->dc_2 = data->dc;
	data->sc_2 = data->sc;
	count_tokens(data);
	save_tokens(data);
	// printf("%d\n", data->count);
	// if (save_tokens(data))
	// 	return (0);
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

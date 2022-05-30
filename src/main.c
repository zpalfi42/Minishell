/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/05/30 17:09:20 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i] != 0)
	{
		free(data->tokens[i]);
		i++;
	}
	free(data->tokens[i]);
	free(data->tokens);
}

void handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
    }
}

void	init_data(t_data *data)
{
	data->n_dc = 0;
	data->n_sc = 0;
	data->word = 0;
}

int	save_word(t_data *data, int i, char c)
{
	int j;
	int z;

	j = 0;
	while (data->line[i + j] != c && data->line[i + j] != '\0')
		j++;
	data->tokens[data->word] = malloc(sizeof(char) * (j + 1));
	data->tokens[data->word][j] = '\0';
	printf("AAAAA %d\n", j);
	z = 0;
	while (data->line[i + z] != c && data->line[i + z] != '\0')
	{
		printf("AAAAA %d %d\n", z, i);
		data->tokens[data->word][z] = data->line[i + z];
		z++;
	}
	data->word++;
	return (j + 1);
}

static int	dc_case_2(t_data *data, int i)
{
	int j;

	j = 0;
	data->n_dc_2--;
	j++;
	if (data->line[i + j] == '"')
		j++;
	else
		j += save_word(data, i + j, '"');
	return (j);
}

static int	sc_case_2(t_data *data, int i)
{
	int	j;

	j = 0;
	data->n_sc_2--;
	j++;
	if (data->line[i + j] == 39)
		j++;
	else
	{
		j += save_word(data, i + j, 39);
	}
	return (j);
}

void	save_tokens(t_data *data)
{
	int	i;

	i = 0;
	printf("AAAAA\n");
	while (data->line[i] != '\0')
	{
		if (data->line[i] == ' ')
			i++;
		else if (data->line[i] == '"')
		{
			i += dc_case_2(data, i);
		}
		else if (data->line[i] == 39)
		{
			i += sc_case_2(data, i);
		}
		else
		{
			printf("AAAAA\n");
			i += save_word(data, i, ' ');
		}
	}
}

void	parser(t_data *data)
{
	int i;

	i = 0;
	data->n_dc = 0;
	data->n_sc = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == '"')
			data->n_dc++;
		else if (data->line[i] == 39)
			data->n_sc++;
		i++;
	}
	data->n_dc_2 = data->n_dc;
	data->n_sc_2 = data->n_sc;
	count_words(data);
	data->tokens = (char **)malloc(sizeof(char *) * (data->count + 1));
	if (!data->tokens)
	{
		printf("MALLOC ERROR\n");
		exit(1);
	}
	data->tokens[data->count] = 0;
	save_tokens(data);
	printf("%s\n", data->tokens[0]);
	printf("%s\n", data->tokens[1]);
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
	signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
	signal(SIGINT, handler);
	init_data(data);
	while (42)
	{
		data->n_dc = 0;
		data->n_sc = 0;
		data->count = 0;
		data->word = 0;
		data->line = readline("miniconcha>$ ");
		if (data->line)
			parser(data);
		else
		{
			free(data);
			exit (1);
		}
	}
}

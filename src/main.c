/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/05/30 15:27:55 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	data->n_c = 0;
}

void	count_words(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == ' ')
			i++;
		else if (data->line[i] == '"')
		{
			i++;
			if (data->line[i] == '"')
				i++;
			else
			{
				data->count++;
				while (data->line[i] && data->line[i] != '"')
					i++;
				i++;
			}
		}
		else
		{
			data->count++;
			while (data->line[i] && data->line[i] != ' ')
				i++;
		}
	}
}

void	parser(t_data *data)
{
	int i;

	i = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == '"')
			data->n_c++;
		i++;
	}
	//printf("%d\n", data->n_c);
	count_words(data);
	printf("%d\n", data->count);
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
		data->n_c = 0;
		data->count = 0;
		data->line = readline("miniconcha>$ ");
		if (data->line)
			parser(data);
		else
			exit (1);
	}
}

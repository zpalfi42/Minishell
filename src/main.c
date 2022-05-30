/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/05/30 16:06:45 by zpalfi           ###   ########.fr       */
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
	data->n_dc = 0;
	data->n_sc = 0;
}

void	parser(t_data *data)
{
	int i;

	i = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == '"')
			data->n_dc++;
		else if (data->line[i] == 39)
			data->n_sc++;
		i++;
	}
	count_words(data);
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
		data->line = readline("miniconcha>$ ");
		if (data->line)
			parser(data);
		else
			exit (1);
	}
}

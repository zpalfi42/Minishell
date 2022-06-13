/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/13 16:34:32 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_data *data)
{
	parser(data);
	ast(data);
	free_all(data);
}

void	routine(t_data *data)
{
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
		{
			add_history(data->line);
			minishell(data);
		}
		free(data->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argc;
	(void) argv;
	print_miniconcha();
	data = (t_data *)malloc(sizeof(t_data));
	if (sig_handler())
		return (1);
	data->env = init_env(envp);
	routine(data);
}

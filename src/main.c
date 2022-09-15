/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/15 12:40:23 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	minishell(t_data *data)
{
	parser(data);
	if (pipe_parser(data) == -1)
		free_all(data);
	else
	{
		ast(data);
		free_all(data);
	}
}

void	routine(t_data *data)
{
	save_home_data(data, 1);
	while (42)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		data->count = 0;
		data->word = 0;
		data->line = readline("\033[1;32mminiconcha>$ \033[1;00m");
		if (data->line == 0)
		{
			free_exit(data);
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
	g_status = 0;
	print_miniconcha();
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error(data, "Failed malloc :(");
	if (sig_handler())
		return (1);
	if (envp_init(data, envp))
		ft_error(data, "Failed maloc :(");
	routine(data);
}
